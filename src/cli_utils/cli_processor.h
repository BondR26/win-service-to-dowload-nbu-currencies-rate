//
// Created by 26bon on 2/14/2024.
//

#ifndef COOL_PROJECT_CLI_PROCESSOR_H
#define COOL_PROJECT_CLI_PROCESSOR_H

#include "cli_utils.h"

namespace cli_utils
{

    class CliProcessor {
    public:

        CliProcessor(int argc, char *argv[]);

        ~CliProcessor();

        const std::string &getServicePath() const;

        CliCommand getCommand1() const;
    private:
        int _argc;
        CliCommand _command;
        std::string _service_path;
    };

}

#endif //COOL_PROJECT_CLI_PROCESSOR_H
