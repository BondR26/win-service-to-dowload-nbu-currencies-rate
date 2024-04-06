//
// Created by 26bon on 2/15/2024.
//

#ifndef COOL_PROJECT_RESOURCES_NAME_H
#define COOL_PROJECT_RESOURCES_NAME_H

#include <map>
#include <string>


namespace resources_name
{
    constexpr const char* subKey = "SOFTWARE\\CoolCurrencyProj";

    enum class FetchRate : int
    {
        EVERY_MINUTE,
        EVERY_TWO_MINUTES,
        EVERY_FIVE_MINUTES,
    };

    enum class DataFormat : int
    {
        JSON,
        XML,
        CSV
    };

    namespace registry_key_names
    {
        constexpr const char* FETCH_RATE  = "fetch_rate";
        constexpr const char* DATA_FORMAT = "data_format";

        constexpr const char* FULL_FETCH_RATE = "SOFTWARE\\CoolCurrencyProj\\fetch_rate";
        constexpr const char* FULL_DATA_FORMAT = "SOFTWARE\\CoolCurrencyProj\\data_format";
    }

    namespace registry_key_values
    {
        constexpr const char* JSON = "json";
        constexpr const char* XML  = "xml";
        constexpr const char* CSV  = "csv";

        constexpr const char* EVERY_MINUTE       = "minute";
        constexpr const char* EVERY_TWO_MINUTES  = "two_minutes";
        constexpr const char* EVERY_FIVE_MINUTES = "five_minutes";
    }

    constexpr const char* CONFIG_FILE = "config.json";

    FetchRate fetch_rate_to_enum(const std::string& fetch_rate_);

    DataFormat data_format_to_enum(const std::string& data_format_);
}

#endif //COOL_PROJECT_RESOURCES_NAME_H
