//
// Created by 26bon on 2/12/2024.
//
#include "registry_util.h"

#include <Windows.h>
#include <iostream>
#include "config/resources_name.h"


LPCSTR str_to_lpcstr(const std::string& str)
{
    return str.c_str();
}

void RegistryUtil::createRegistryKey(const std::string& name, const std::string& value) const
{
    HKEY hKey;

    LONG result = RegCreateKeyEx( HKEY_LOCAL_MACHINE
                                , resources_name::subKey
                                , 0
                                , NULL
                                , REG_OPTION_NON_VOLATILE
                                , KEY_WRITE
                                , NULL
                                , &hKey
                                , NULL);

    if (result == ERROR_SUCCESS)
    {
        result = RegSetValueEx(hKey
                              , name.c_str()
                              , 0
                              , REG_SZ
                              , (BYTE*)value.data()
                              , value.size());

        if (result == ERROR_SUCCESS)
        {
            std::cout << "String value set successfully." << std::endl;
        } else {
            std::cerr << "Failed to set string value. Error code: " << result << std::endl;
        }

        RegCloseKey(hKey);
    }
    else
    {
        std::cerr << "Failed to create registry key. Error code: " << result << std::endl;
    }
}

void RegistryUtil::readRegistryKey(const std::string& name_, std::string& value)    const
{
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, resources_name::subKey, 0, KEY_READ, &hKey);

    if (result == ERROR_SUCCESS)
    {
        char buffer[512];
        DWORD bufferSize = sizeof(buffer);
        result = RegQueryValueEx(hKey, name_.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize);

        if (result == ERROR_SUCCESS)
        {
            value = buffer;
            std::cout << "Value: " << buffer << std::endl;
        } else {
            std::cerr << "Failed to read registry key. Error code: " << result << std::endl;
        }

        RegCloseKey(hKey);
    }
    else
    {
        std::cerr << "Failed to open registry key. Error code: " << result << std::endl;
    }
}

void RegistryUtil::deleteRegistryKey() const
{

    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, resources_name::subKey, 0, KEY_READ, &hKey);

    if (result == ERROR_SUCCESS)
    {
        LONG result = RegDeleteKey(HKEY_LOCAL_MACHINE, resources_name::subKey);

        if (result == ERROR_SUCCESS) {
            std::cout << "Registry key deleted successfully." << std::endl;
        } else {
            std::cerr << "Failed to delete registry key. Error code: " << result << std::endl;
        }
    }
    else
    {
        std::cout << "Registry key doesnt exist" << result << std::endl;
    }
}

RegistryUtil::~RegistryUtil()
{
    std::cout << "RegistryUtil destructor" << std::endl;

    //deleteRegistryKey();
}

RegistryUtil::RegistryUtil()
{

}

void RegistryUtil::updateRegistryKey(const std::string &name, const std::string &value) const
{
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, resources_name::subKey, 0, KEY_WRITE, &hKey);

    if (result == ERROR_SUCCESS)
    {
        result = RegSetValueEx(hKey, name.c_str(), 0, REG_SZ, (BYTE*)value.data(), value.size());

        if (result == ERROR_SUCCESS)
        {
            std::cout << "String value updated successfully." << std::endl;
        } else {
            std::cerr << "Failed to update string value. Error code: " << result << std::endl;
        }

        RegCloseKey(hKey);
    }
    else
    {
        std::cerr << "Failed to open registry key. Error code: " << result << std::endl;
    }

}

time_t getRegistryModificationTimestamp(HKEY hKey, LPCSTR lpSubKey)
{
    FILETIME lastWriteTime;

    DWORD dwSize = sizeof(FILETIME);
    // Query the last write time of the registry key
    if (RegQueryInfoKey(hKey
                        , NULL
                        , NULL
                        , NULL
                        , NULL
                        , NULL
                        , NULL
                        , NULL
                        , NULL
                        , NULL
                        , NULL
                        , &lastWriteTime) == ERROR_SUCCESS)
    {
        // Convert FILETIME to time_t
        ULARGE_INTEGER uli;
        uli.LowPart = lastWriteTime.dwLowDateTime;
        uli.HighPart = lastWriteTime.dwHighDateTime;

        return uli.QuadPart / 10000000ULL - 11644473600ULL; // Convert 100-nanosecond intervals to Unix time
    }

    // Error handling
    return 0;
}

uint64_t RegistryUtil::getLastWriteTime()
{
    HKEY hKey;
    // Open the registry key
    auto res = RegOpenKeyEx(HKEY_LOCAL_MACHINE
                    //, resources_name::registry_key_names::FULL_FETCH_RATE
                    , resources_name::subKey
                    , 0
                    , KEY_READ
                    , &hKey);
    if (ERROR_SUCCESS == res)
    {
        // Get the modification timestamp of the registry key
        time_t lastWriteTime = getRegistryModificationTimestamp(hKey, resources_name::subKey);

        // Close the registry key
        RegCloseKey(hKey);

        return lastWriteTime;
    }
    else
    {
        // Error handling
        std::cout << "Error: Unable to open registry key" << std::endl;
    }

    return 0;
}

const RegistryUtil& RegistryUtil::instance()
{
    return _instance;
}

RegistryUtil RegistryUtil::_instance;