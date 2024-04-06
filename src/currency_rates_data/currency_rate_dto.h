//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_CurrencyRateDTO_H
#define COOL_PROJECT_CurrencyRateDTO_H
#include <nlohmann/json.hpp>


class CurrencyRateDTO
{
public:
    CurrencyRateDTO();
    ~CurrencyRateDTO();

    friend void from_json(const nlohmann::json& j, CurrencyRateDTO& cr);

    friend void to_json(nlohmann::json& j, const CurrencyRateDTO& cr);

    unsigned int getId() const;

    const std::wstring &getName() const;

    double getRate() const;

    const std::string &getCurrencyCode() const;

    const std::string &getExchangeDate() const;

private:
    unsigned _id;
    std::wstring _name;
    double _rate;
    std::string _currency_code;
    std::string _exchange_date;
};

#endif //COOL_PROJECT_CurrencyRateDTO_H
