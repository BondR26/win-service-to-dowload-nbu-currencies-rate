//
// Created by 26bon on 2/13/2024.
//
#include <pugixml.hpp>
#include <sstream>
#include "xml_formatter.h"
#include "currency_rates_data/data.h"


void addCurrencyNode(pugi::xml_node parent, const CurrencyRateDTO& currency)
{
    pugi::xml_node currencyNode = parent.append_child("currency");
    currencyNode.append_attribute("r030").set_value(currency.getId());
    currencyNode.append_attribute("txt").set_value(currency.getName().c_str());
    currencyNode.append_attribute("rate").set_value(currency.getRate());
    currencyNode.append_attribute("cc").set_value(currency.getCurrencyCode().c_str());
    currencyNode.append_attribute("exchangedate").set_value(currency.getExchangeDate().c_str());
}


std::wstring XMLFormatter::format(const Data &data_)
{
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("exchange");
    for (auto& currnecy : data_.getCurrencyRates())
    {
        addCurrencyNode(root, currnecy);
    }

    std::wstringstream oss;
    doc.save(oss);

    return oss.str();
}

XMLFormatter::XMLFormatter() {

}

XMLFormatter::~XMLFormatter() {

}

