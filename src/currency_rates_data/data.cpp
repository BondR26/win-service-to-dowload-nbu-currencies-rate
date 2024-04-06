//
// Created by 26bon on 2/12/2024.
//
#include "data.h"

Data::Data() {

}

Data::~Data() {

}

void Data::add(const nlohmann::json &j)
{
    for(const auto& el : j)
    {
        CurrencyRateDTO rate = el;
        _currency_rates.emplace_back(rate);
    }
}

const std::vector<CurrencyRateDTO> &Data::getCurrencyRates() const {
    return _currency_rates;
}

bool Data::is_empty() const
{
    return _currency_rates.empty();
}