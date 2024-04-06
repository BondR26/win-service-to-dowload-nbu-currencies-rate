//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_CONFIG_DTO_H
#define COOL_PROJECT_CONFIG_DTO_H


#include <nlohmann/json.hpp>
#include "configurations.h"
#include "resources_name.h"


NLOHMANN_JSON_SERIALIZE_ENUM(resources_name::FetchRate, {
    {resources_name::FetchRate::EVERY_TWO_MINUTES, "day"},
    {resources_name::FetchRate::EVERY_FIVE_MINUTES, "week"},
    {resources_name::FetchRate::MONTHLY, "month"}
})

NLOHMANN_JSON_SERIALIZE_ENUM(resources_name::DataFormat, {
    {resources_name::DataFormat::JSON, "json"},
    {resources_name::DataFormat::XML, "xml"},
    {resources_name::DataFormat::CSV, "csv"}
})

class ConfigDTO
{
public:

    ConfigDTO();

    ConfigDTO(resources_name::FetchRate fetch_rate, resources_name::DataFormat data_format);

    ~ConfigDTO();

    friend void from_json(const nlohmann::json& j, ConfigDTO& config);

    friend void to_json(nlohmann::json& j, const ConfigDTO& config);

    resources_name::FetchRate getFetchRate() const;

    resources_name::DataFormat getDataFormat() const;

private:
    resources_name::FetchRate _fetch_rate;
    resources_name::DataFormat _data_format;
};


#endif //COOL_PROJECT_CONFIG_DTO_H
