//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_CONFIG_READER_H
#define COOL_PROJECT_CONFIG_READER_H

#include "configurations.h"

class ConfigReader
{
public:
    ConfigReader();
    ~ConfigReader();
    virtual Configurations read() = 0;
};

#endif //COOL_PROJECT_CONFIG_READER_H
