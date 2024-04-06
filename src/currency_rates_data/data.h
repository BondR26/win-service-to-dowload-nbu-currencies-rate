//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_DATA_H
#define COOL_PROJECT_DATA_H

#include <vector>
#include "currency_rate_dto.h"


class Data
{
public:
    Data();
    ~Data();

    void add(const nlohmann::json& j);

    const std::vector<CurrencyRateDTO> &getCurrencyRates() const;

    bool is_empty() const;

private:
    std::vector<CurrencyRateDTO> _currency_rates;
};

#endif //COOL_PROJECT_DATA_H
