//
// Created by 26bon on 2/12/2024.
//
#include "config_dto.h"
#include "resources_name.h"


void from_json(const nlohmann::json &j, ConfigDTO &config)
{
    if(j.contains(resources_name::registry_key_names::FETCH_RATE))
    {
        j.at(resources_name::registry_key_names::FETCH_RATE).get_to(config._fetch_rate);
    }

    if(j.contains(resources_name::registry_key_names::DATA_FORMAT))
    {
        j.at(resources_name::registry_key_names::DATA_FORMAT).get_to(config._data_format);
    }
}

resources_name::FetchRate ConfigDTO::getFetchRate() const {
    return _fetch_rate;
}

resources_name::DataFormat ConfigDTO::getDataFormat() const {
    return _data_format;
}

ConfigDTO::ConfigDTO() {

}

ConfigDTO::~ConfigDTO() {

}

void to_json(nlohmann::json &j, const ConfigDTO &config)
{
    j[resources_name::registry_key_names::FETCH_RATE]  = config._fetch_rate;
    j[resources_name::registry_key_names::DATA_FORMAT] = config._data_format;

}

ConfigDTO::ConfigDTO(resources_name::FetchRate fetch_rate, resources_name::DataFormat data_format) {
    _fetch_rate = fetch_rate;
    _data_format = data_format;

}

