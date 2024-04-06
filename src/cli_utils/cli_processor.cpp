//
// Created by 26bon on 2/14/2024.
//
#include <map>
#include <string>
#include <iostream>
#include "cli_processor.h"


namespace cli_utils {

    CliProcessor::CliProcessor(int argc, char *argv[])
            : _argc(argc)
    {
        _service_path = argv[0];

        auto command = getCommand(argv[argc - 1]);
        if (command != CliCommand::NONE)
        {
            std::cout << "Processing command: " << getCommandName(command) << "\n";
            _command = command;
        }
        else
        {
            std::cout << "Unknown command: " << argv[argc - 1] << "\n";
            _command = CliCommand::NONE;
        }
    }

    const std::string &CliProcessor::getServicePath() const
    {
        return _service_path;
    }

    CliProcessor::~CliProcessor() {

    }

    CliCommand CliProcessor::getCommand1() const
    {
        return _command;
    }
}