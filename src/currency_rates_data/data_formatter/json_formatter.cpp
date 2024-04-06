//
// Created by 26bon on 2/13/2024.
//
#include <sstream>
#include <codecvt>
#include "json_formatter.h"
#include "currency_rates_data/data.h"
#include "string_utils.h"


std::wstring JSONFormatter::format(const Data &data_)
{
    nlohmann::json json = data_.getCurrencyRates();
    auto str = json.dump();
    std::wstring formatted_data = std::from_utf8(str);
    return formatted_data;
}

JSONFormatter::JSONFormatter() {

}

JSONFormatter::~JSONFormatter() {

}

