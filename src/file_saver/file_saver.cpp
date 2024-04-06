//
// Created by 26bon on 2/12/2024.
//
#include <map>
#include <chrono>
#include <fstream>
#include <sstream>
#include "file_saver.h"

FileSaver::FileSaver()
{

}

FileSaver::~FileSaver()
{

}

const std::map<resources_name::DataFormat, std::string> file_ext =
{
    {resources_name::DataFormat::JSON, ".json"},
    {resources_name::DataFormat::XML,  ".xml"},
    {resources_name::DataFormat::CSV,  ".csv"}
};

void FileSaver::save(const std::wstring &_content, resources_name::DataFormat _format)
{
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::stringstream timestamp;
    timestamp << (now->tm_year + 1900) << '_' << (now->tm_mon + 1) << '_' <<  now->tm_mday << '_' << now->tm_hour << '_' << now->tm_min << '_' << now->tm_sec;

    std::string file_name = timestamp.str() + "_currency_rates" + file_ext.find(_format)->second.c_str();

    std::ofstream file(file_name,std::ios::binary);

    file.write(reinterpret_cast<const char *>(_content.data()), _content.size() * sizeof(wchar_t));

    // Close file
    file.close();
}

