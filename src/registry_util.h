//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_REGISTRY_UTIL_H
#define COOL_PROJECT_REGISTRY_UTIL_H

#include <string>


class RegistryUtil
{
public:

    static const RegistryUtil& instance();

    ~RegistryUtil();

    void createRegistryKey(const std::string& name, const std::string& value) const;

    void readRegistryKey(const std::string& name, std::string& value) const;

    static uint64_t getLastWriteTime();

    void deleteRegistryKey() const;

    void updateRegistryKey(const std::string& name, const std::string& value) const;

private:
    RegistryUtil();
    static RegistryUtil _instance;
};


#endif //COOL_PROJECT_REGISTRY_UTIL_H
