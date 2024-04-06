//
// Created by 26bon on 2/15/2024.
//
#include "formatter_factory.h"
#include "config/resources_name.h"
#include "formatter_interface.h"
#include "json_formatter.h"
#include "csv_formatter.h"
#include "xml_formatter.h"


class FactoryInterface
{
public:
    FactoryInterface() {  }
    virtual ~FactoryInterface() {  }
    virtual FormatterInterface* produce(){return nullptr; }
};

template <class T>
class FormatterFactory : public FactoryInterface
{
public:
    FormatterFactory() {  }
    ~FormatterFactory()
    {
    }


    FormatterInterface* produce() override
    {
        return new T();
    }
};

const std::map<resources_name::DataFormat, FactoryInterface*> factories =
{
    { resources_name::DataFormat::JSON, new FormatterFactory<JSONFormatter>() },
    { resources_name::DataFormat::XML , new FormatterFactory<XMLFormatter>()  },
    { resources_name::DataFormat::CSV , new FormatterFactory<CSVFormatter>()  }
};

std::unique_ptr<FormatterInterface> createFormatter(resources_name::DataFormat format)
{
    auto it = factories.find(format);
    if (it != factories.end())
    {
        return std::unique_ptr<FormatterInterface>(it->second->produce());
    }
    return nullptr;
}