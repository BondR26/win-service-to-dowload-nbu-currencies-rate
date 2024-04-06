//
// Created by 26bon on 2/15/2024.
//

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <thread>
#include <condition_variable>
#include "currency_job.h"
#include "registry_util.h"
#include "config/resources_name.h"
#include "config/config_dto.h"
#include "currency_rates_data/fetcher.h"
#include "config/file_reader.h"
#include "config/registry_reader.h"
#include "currency_rates_data/data_formatter/formatter_interface.h"
#include "currency_rates_data/data_formatter/formatter_factory.h"


namespace currency_job
{
    CurrencyMonitor::CurrencyMonitor() {

    }

    CurrencyMonitor::~CurrencyMonitor() {

    }

    void CurrencyMonitor::init()
    {
        {
            // create registry keys
            auto& registryUtil = RegistryUtil::instance();
            registryUtil.createRegistryKey(resources_name::registry_key_names::DATA_FORMAT, resources_name::registry_key_values::JSON);
            registryUtil.createRegistryKey(resources_name::registry_key_names::FETCH_RATE, resources_name::registry_key_values::EVERY_MINUTE);
        }

        {
            // create config file
            std::ofstream file(resources_name::CONFIG_FILE, std::ios::out | std::ios::trunc);
            if(file.is_open())
            {
                nlohmann::json json = ConfigDTO(resources_name::FetchRate::EVERY_MINUTE, resources_name::DataFormat::JSON);
                file << json;
            }
            file.close();
        }

        _last_json_modification_time    = getLastWriteTime(resources_name::CONFIG_FILE);

        _last_reg_key_modification_time = RegistryUtil::getLastWriteTime();

        // create connection with nbu website
        _curl = std::make_shared<SmartCurl>();

        // create a reader for the configuration
        config_reader = std::make_unique<FileReader>();
    }

    void CurrencyMonitor::monitor_config_src()
    {
        while(is_active)
        {
            std::cout << "Monitoring configurations" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            //std::unique_lock<std::mutex> lock(_mutex);
            // create en event which would be triggered if the config file or registry keys are changed
            // get when the json file was last modified
            auto json_file_modification_time = getLastWriteTime(resources_name::CONFIG_FILE);
            // get when the reg key was last modified
            auto registry_modification_time  = RegistryUtil::getLastWriteTime();

            if(_last_json_modification_time != json_file_modification_time)
            {
                _is_modified = true;
                _last_json_modification_time = json_file_modification_time;
            }

            if(_last_reg_key_modification_time != registry_modification_time)
            {
                _is_modified = true;
                _last_reg_key_modification_time = registry_modification_time;
            }

            if(_is_modified)
            {
                std::cout << "Configurations modified" << std::endl;
                // trigger the update of the configuration
                congifurations_modified.notify_one();
            }
        }

        std::cout << "Monitoring configurations stopped" << std::endl;
        std::cout << "Sending signale to stop updating" << std::endl;
        _is_modified = true;
        congifurations_modified.notify_one();
    }

    void CurrencyMonitor::update_config_reader()
    {
        while(is_active)
        {
            std::cout << "Waiting for configurations to be modified" << std::endl;
            std::unique_lock<std::mutex> lock(_mutex);
            congifurations_modified.wait(lock, [&](){ return _is_modified;});

            std::cout << "Configurations are being modified" << std::endl;

            // check which one was modified last
            if (_last_json_modification_time > _last_reg_key_modification_time)
            {
                config_reader = std::make_unique<FileReader>();
            }
            else
            {
                config_reader = std::make_unique<RegistryReader>();
            }

            _is_modified = false;

            // after we establish new config reader we need to notify the main thread that
            // it should save data using new configurations
            _save_data = true;
            std::cout << "Notify to save data" << std::endl;
            _scheduler.notify_one();
        }
    }

    void CurrencyMonitor::do_the_job()
    {
        is_active = true;

        std::thread update_configs(&CurrencyMonitor::update_config_reader, this);

        std::thread monitor_change_in_configs(&CurrencyMonitor::monitor_config_src, this);

        while(is_active)
        {
            // read the configurations of next saving operation
            Configurations config;
            {
                std::lock_guard<std::mutex> lock(_mutex);
                config = config_reader->read();
            }
            // fetch data from website
            Data res_data = _fetcher.fetch(_curl);
            // check if data is empty
            if (res_data.is_empty())
            {
                std::cout << "Error in fetching data from website" << std::endl;
                continue;
            }

            // based on the configuration create a formatter to format the data
            std::unique_ptr<FormatterInterface> formatter = createFormatter(config.getDataFormat());

            auto res = formatter->format(res_data);

            _file_saver.save(res, config.getDataFormat());

            // set the next saving time
            this->scheduleNextSave(config.getFetchRate());
        }
        // save data to file

        update_configs.join();
        monitor_change_in_configs.join();
    }

    void CurrencyMonitor::stop_the_job()
    {
        is_active = false;
        _scheduler.notify_one();
    }

    std::map<resources_name::FetchRate, std::chrono::seconds> fetch_rate_to_seconds =
    {
        //{resources_name::FetchRate::EVERY_HOUR, std::chrono::hours(1)   },
        //{resources_name::FetchRate::DAILY     , std::chrono::hours(24)  },
        //{resources_name::FetchRate::WEEKLY    , std::chrono::hours(7*24)}
        {resources_name::FetchRate::EVERY_MINUTE,           std::chrono::seconds(600)   },
        {resources_name::FetchRate::EVERY_TWO_MINUTES     , std::chrono::seconds(120)  },
        {resources_name::FetchRate::EVERY_FIVE_MINUTES    , std::chrono::seconds(360)}
    };

    void CurrencyMonitor::scheduleNextSave(resources_name::FetchRate rate)
    {
        std::unique_lock<std::mutex> lock(_scheduler_mutex);
        _scheduler.wait_until( lock
                              , fetch_rate_to_seconds.find(rate)->second + std::chrono::system_clock::now()
                              // if the job is stopped or the configuration is modified
                              , [&](){ return _save_data || !is_active; });

        _save_data = false;

        if(!is_active)
        {
            std::cout << "Signal to stop the service" << std::endl;
        }
    }
}
