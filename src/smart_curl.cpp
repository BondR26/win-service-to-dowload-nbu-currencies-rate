//
// Created by 26bon on 2/12/2024.
//
#include <nlohmann/json.hpp>
#include <iostream>
#include "smart_curl.h"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *data)
{
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}

SmartCurl::SmartCurl()
{
    _curl = curl_easy_init();

    if (_curl)
    {
        curl_easy_setopt(_curl, CURLOPT_URL, url);
        curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);

    }
    else
    {
        std::cout << "Error initializing curl." << std::endl;
    };
}

SmartCurl::~SmartCurl()
{
    curl_easy_cleanup(_curl);
}


nlohmann::json SmartCurl::getResponse()
{
    // clear response before getting new data
    if(!response.empty())
    {
        response.clear();
    }

    res = curl_easy_perform(_curl);

    if (res == CURLE_OK)
    {
        // Parse JSON
        nlohmann::json jsonData;
        try {
            jsonData = nlohmann::json::parse(response);
        }
        catch (const nlohmann::json::exception &e)
        {
            std::cout << "Error parsing JSON: " << e.what() << std::endl;
        }

        return jsonData;

    } else {
        std::cout << "Error downloading file: " << curl_easy_strerror(res) << std::endl;
        return error_msg;
    }
}