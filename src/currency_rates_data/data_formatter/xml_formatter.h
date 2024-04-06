//
// Created by 26bon on 2/13/2024.
//

#ifndef COOL_PROJECT_XML_FORMATTER_H
#define COOL_PROJECT_XML_FORMATTER_H

#include "formatter_interface.h"

class XMLFormatter : public FormatterInterface
{
public:
    XMLFormatter();
    ~XMLFormatter();

    virtual std::wstring format(const Data& data_) override;
};

#endif //COOL_PROJECT_XML_FORMATTER_H
