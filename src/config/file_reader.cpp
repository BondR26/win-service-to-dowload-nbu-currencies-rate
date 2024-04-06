//
// Created by 26bon on 2/12/2024.
//
#include "file_reader.h"
#include "config_dto.h"
#include "resources_name.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <Windows.h>


Configurations FileReader::read()
{
    std::ifstream file(resources_name::CONFIG_FILE);

    if(file.is_open())
    {
        std::cout << "File opened successfully" << std::endl;

        //read file into buffer
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        if(content.empty())
        {
            std::cout << "File is empty" << std::endl;
        }

        nlohmann::json json;
        try {
            json = nlohmann::json::parse(content);
        }
        catch (nlohmann::json::parse_error& e)
        {
            std::cout << "Error parsing json: " << e.what() << std::endl;
        }

        ConfigDTO configDTO = json;

        return {configDTO.getFetchRate(), configDTO.getDataFormat()};

    }

    std::cout << "File could not be opened or read correctly; Setting default configs" << std::endl;
    return {};
}

FileReader::FileReader() {

}

FileReader::~FileReader() {

}

time_t getFileModificationTimestamp(const std::string& filePath)
{
    FILETIME lastWriteTime;
    ULARGE_INTEGER uli;

    // Open the file
    HANDLE hFile = CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        // Error handling
        return 0;
    }

    // Get the last write time of the file
    if (!GetFileTime(hFile, NULL, NULL, &lastWriteTime))
    {
        // Error handling
        CloseHandle(hFile);
        return 0;
    }

    CloseHandle(hFile);

    // Convert FILETIME to time_t
    uli.LowPart = lastWriteTime.dwLowDateTime;
    uli.HighPart = lastWriteTime.dwHighDateTime;

    return uli.QuadPart / 10000000ULL - 11644473600ULL; // Convert 100-nanosecond intervals to Unix time
}

uint64_t getLastWriteTime(const std::string& path)
{
    return getFileModificationTimestamp(path);
}