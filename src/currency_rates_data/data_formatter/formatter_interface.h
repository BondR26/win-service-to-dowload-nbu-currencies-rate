//
// Created by 26bon on 2/13/2024.
//

#ifndef COOL_PROJECT_EXPORTER_INTERFACE_H
#define COOL_PROJECT_EXPORTER_INTERFACE_H
#include <string>

class Data;
class FormatterInterface
{
public:
    FormatterInterface();
    virtual ~FormatterInterface();

    virtual std::wstring format(const Data& data_) = 0;
};

#endif //COOL_PROJECT_EXPORTER_INTERFACE_H
