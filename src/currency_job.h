//
// Created by 26bon on 2/15/2024.
//

#ifndef COOL_PROJECT_CURRENCY_JOB_H
#define COOL_PROJECT_CURRENCY_JOB_H

#include "currency_rates_data/fetcher.h"
#include "file_saver/file_saver.h"
#include "registry_util.h"
#include <mutex>
#include <condition_variable>
#include <atomic>


class SmartCurl;
class ConfigReader;

namespace currency_job
{
    class CurrencyMonitor
    {
    public:
        CurrencyMonitor();
        ~CurrencyMonitor();

        void init();
        void do_the_job();
        void stop_the_job();

    private:

        void monitor_config_src();
        void update_config_reader();

        std::shared_ptr<SmartCurl> _curl;
        CurrencyRateFetcher _fetcher;
        FileSaver _file_saver;

        uint64_t _last_json_modification_time   ;
        uint64_t _last_reg_key_modification_time;

        std::unique_ptr<ConfigReader> config_reader;

        bool _is_modified = false;
        std::mutex _mutex;
        std::condition_variable congifurations_modified;


        bool _save_data = false;
        std::mutex _scheduler_mutex;
        std::condition_variable _scheduler;

        std::atomic<bool> is_active;

        void scheduleNextSave(resources_name::FetchRate rate);
    };

}

#endif //COOL_PROJECT_CURRENCY_JOB_H
