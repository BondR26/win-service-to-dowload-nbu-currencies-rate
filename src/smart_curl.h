//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_SMART_CURL_H
#define COOL_PROJECT_SMART_CURL_H

#include <curl/curl.h>
#include <string>

constexpr const char* url = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchange?json";
constexpr const char* error_msg = "Error in getting response";


class SmartCurl
{
public:
    SmartCurl();
    ~SmartCurl();

    [[nodiscard]]
    nlohmann::json getResponse();

private:
    CURL* _curl;
    CURLcode res;
    std::string response;
};


#endif //COOL_PROJECT_SMART_CURL_H
