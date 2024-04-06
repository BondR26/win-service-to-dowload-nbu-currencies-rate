//
// Created by 26bon on 2/15/2024.
//

#ifndef COOL_PROJECT_FORMATTER_FACTORY_H
#define COOL_PROJECT_FORMATTER_FACTORY_H

#include <string>
#include <memory>
#include "config/resources_name.h"

class FormatterInterface;

std::unique_ptr<FormatterInterface> createFormatter(resources_name::DataFormat format);

#endif //COOL_PROJECT_FORMATTER_FACTORY_H