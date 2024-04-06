//
// Created by 26bon on 2/15/2024.
//
#include "resources_name.h"

const std::map<std::string, resources_name::FetchRate> gFetchRateMap =
        {
                {resources_name::registry_key_values::EVERY_TWO_MINUTES , resources_name::FetchRate::EVERY_TWO_MINUTES   },
                {resources_name::registry_key_values::EVERY_MINUTE,       resources_name::FetchRate::EVERY_MINUTE },
                {resources_name::registry_key_values::EVERY_FIVE_MINUTES , resources_name::FetchRate::EVERY_FIVE_MINUTES  }
        };

const std::map<std::string, resources_name::DataFormat> regDataFormatMap =
        {
                {resources_name::registry_key_values::JSON , resources_name::DataFormat::JSON },
                {resources_name::registry_key_values::XML  , resources_name::DataFormat::XML  },
                {resources_name::registry_key_values::CSV  , resources_name::DataFormat::CSV  }
        };


resources_name::FetchRate resources_name::fetch_rate_to_enum(const std::string &fetch_rate_)
{
    return gFetchRateMap.at(fetch_rate_);
}

resources_name::DataFormat resources_name::data_format_to_enum(const std::string &data_format_)
{
    return regDataFormatMap.at(data_format_);
}