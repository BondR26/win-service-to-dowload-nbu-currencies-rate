//
// Created by 26bon on 2/13/2024.
//
#include <sstream>
#include "csv_formatter.h"
#include "currency_rates_data/data.h"


std::wstring CSVFormatter::format(const Data &data_)
{
    std::wstringstream formatted_data;

    for(auto& currency : data_.getCurrencyRates())
    {
        formatted_data << currency.getId() << "," << currency.getName().c_str() << "," << currency.getRate() << "," << currency.getCurrencyCode().c_str() << "," << currency.getExchangeDate().c_str() << std::endl;
    }

    return formatted_data.str();
}

CSVFormatter::CSVFormatter() {

}

CSVFormatter::~CSVFormatter() {

}

