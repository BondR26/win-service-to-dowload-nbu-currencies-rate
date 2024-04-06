//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_REGISTRY_READER_H
#define COOL_PROJECT_REGISTRY_READER_H
#include "config_reader.h"


class RegistryReader : public ConfigReader
{
    public:
    RegistryReader();
    ~RegistryReader();
    virtual Configurations read() override;
};

#endif //COOL_PROJECT_REGISTRY_READER_H
