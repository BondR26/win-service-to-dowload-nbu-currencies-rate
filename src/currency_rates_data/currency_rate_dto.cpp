//
// Created by 26bon on 2/12/2024.
//
#include <nlohmann/json.hpp>
#include <codecvt>
#include "currency_rate_dto.h"
#include "currency_rates_data/data_formatter/string_utils.h"


std::wstring utf8ToWideString(const std::string& utf8Str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(utf8Str);
}

void from_json(const nlohmann::json &j, CurrencyRateDTO &cr)
{
    if (j.contains("r030"))
        j.at("r030").get_to(cr._id);

    if (j.contains("txt"))
    {
        cr._name = utf8ToWideString(j.at("txt"));
    }

    if (j.contains("rate"))
        j.at("rate").get_to(cr._rate);

    if (j.contains("cc"))
        j.at("cc").get_to(cr._currency_code);

    if (j.contains("exchangedate"))
        j.at("exchangedate").get_to(cr._exchange_date);
}

CurrencyRateDTO::CurrencyRateDTO() {

}

CurrencyRateDTO::~CurrencyRateDTO() {

}

void to_json(nlohmann::json &j, const CurrencyRateDTO &cr)
{
    // alternative way to convert std::wstring to std::string
    j["r030"] = cr._id;
    //j["txt"] = cr._name;
    j["txt"] = std::to_utf8(cr._name);
    j["rate"] = cr._rate;
    j["cc"] = cr._currency_code;
    j["exchangedate"] = cr._exchange_date;
}

unsigned int CurrencyRateDTO::getId() const {
    return _id;
}

const std::wstring &CurrencyRateDTO::getName() const {
    return _name;
}

double CurrencyRateDTO::getRate() const {
    return _rate;
}

const std::string &CurrencyRateDTO::getCurrencyCode() const {
    return _currency_code;
}

const std::string &CurrencyRateDTO::getExchangeDate() const {
    return _exchange_date;
}
