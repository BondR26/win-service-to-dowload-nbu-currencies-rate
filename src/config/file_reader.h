//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_FILE_READER_H
#define COOL_PROJECT_FILE_READER_H
#include "config_reader.h"


class FileReader : public ConfigReader
{
    public:
    FileReader();
    ~FileReader();
    virtual Configurations read() override;
};

uint64_t getLastWriteTime(const std::string& path);

#endif //COOL_PROJECT_FILE_READER_H
