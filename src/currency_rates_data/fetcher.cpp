//
// Created by 26bon on 2/12/2024.
//

// purpose to fetch currency rates from a remote server
#include "fetcher.h"

#include <iostream>


class CurrencyRateFetcherImpl
{
public:
    CurrencyRateFetcherImpl();
    ~CurrencyRateFetcherImpl();

    Data fetch(const std::shared_ptr<SmartCurl> &_curl);

private:

};


CurrencyRateFetcherImpl::~CurrencyRateFetcherImpl() {

}

Data CurrencyRateFetcherImpl::fetch(const std::shared_ptr<SmartCurl> &_curl)
{
    auto response = _curl->getResponse();

    if (response.empty())
    {
        std::cerr << "Error in fetching response from website" << std::endl;
        return Data();
    }

    Data data;

    data.add(response);

    return data;
}


//
// CurrencyRateFetcher
//

CurrencyRateFetcher::CurrencyRateFetcher() {

}

CurrencyRateFetcher::~CurrencyRateFetcher() {

}

Data CurrencyRateFetcher::fetch(const std::shared_ptr<SmartCurl>& _curl)
{
    return _impl->fetch(_curl);
}
