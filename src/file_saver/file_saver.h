//
// Created by 26bon on 2/12/2024.
//

#ifndef COOL_PROJECT_FILE_SAVER_H
#define COOL_PROJECT_FILE_SAVER_H

#include <string>
#include "config/configurations.h"
#include "config/resources_name.h"


class FileSaver
{
public:

    FileSaver();

    ~FileSaver();

    void save(const std::wstring& _content, resources_name::DataFormat _format);

private:

};

#endif //COOL_PROJECT_FILE_SAVER_H
