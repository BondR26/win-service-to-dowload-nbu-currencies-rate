//
// Created by 26bon on 2/13/2024.
//
#include "configurations.h"

Configurations::Configurations()
        : _fetch_rate(resources_name::FetchRate::EVERY_TWO_MINUTES), _data_format(resources_name::DataFormat::JSON)
{

}

Configurations::Configurations(resources_name::FetchRate rate, resources_name::DataFormat format)
        : _fetch_rate (rate)
        , _data_format(format)
{

}

resources_name::FetchRate Configurations::getFetchRate() const {
    return _fetch_rate;
}

resources_name::DataFormat Configurations::getDataFormat() const {
    return _data_format;
}

Configurations::~Configurations() {

}
