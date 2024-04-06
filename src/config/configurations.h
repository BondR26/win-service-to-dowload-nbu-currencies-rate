//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_CONFIGURATIONS_H
#define COOL_PROJECT_CONFIGURATIONS_H

#include "resources_name.h"


class Configurations
{
public:

    Configurations();
    Configurations(resources_name::FetchRate rate, resources_name::DataFormat format);
    ~Configurations();
    resources_name::FetchRate getFetchRate() const;
    resources_name::DataFormat getDataFormat() const;

private:
    resources_name::FetchRate _fetch_rate;
    resources_name::DataFormat _data_format;
};

#endif //COOL_PROJECT_CONFIGURATIONS_H
