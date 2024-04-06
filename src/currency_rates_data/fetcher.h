//
// Created by 26bon on 2/12/2024.
//

#pragma once

#include "data.h"
#include "smart_curl.h"

class CurrencyRateFetcherImpl;

class CurrencyRateFetcher
{
public:
    CurrencyRateFetcher();
    ~CurrencyRateFetcher();

    [[nodiscard]]
    Data fetch(const std::shared_ptr<SmartCurl>& _curl);

private:
    CurrencyRateFetcherImpl* _impl;
};