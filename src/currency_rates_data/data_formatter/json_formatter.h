//
// Created by 26bon on 2/13/2024.
//

#ifndef COOL_PROJECT_JSON_FORMATTER_H
#define COOL_PROJECT_JSON_FORMATTER_H

#include "formatter_interface.h"

class JSONFormatter : public FormatterInterface
{
public:
    JSONFormatter();
    ~JSONFormatter();

    virtual std::wstring format(const Data& data_) override;
};

#endif //COOL_PROJECT_JSON_FORMATTER_H
