//
// Created by 26bon on 2/12/2024.
//
#include "registry_reader.h"

#include <Windows.h>

#include <string>
#include <map>

#include "registry_util.h"
#include "resources_name.h"


Configurations RegistryReader::read()
{
    // read a value from the registry using my api

    std::string fetchRate;
    auto& registryUtil = RegistryUtil::instance();
    registryUtil.readRegistryKey(resources_name::registry_key_names::FETCH_RATE, fetchRate);

    std::string dataFormat;
    registryUtil.readRegistryKey(resources_name::registry_key_names::DATA_FORMAT, dataFormat);

    Configurations configurations(resources_name::fetch_rate_to_enum(fetchRate), resources_name::data_format_to_enum(dataFormat));

    return configurations;
}

RegistryReader::RegistryReader() {

}

RegistryReader::~RegistryReader() {

}
