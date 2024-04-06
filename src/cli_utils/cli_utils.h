//
// Created by 26bon on 2/14/2024.
//

#ifndef COOL_PROJECT_CLI_UTILS_H
#define COOL_PROJECT_CLI_UTILS_H

#include <string>

namespace cli_utils
{

    enum class CliCommand {
        INSTALL,
        REMOVE,
        START,
        STOP,
        STANDALONE,
        NONE
    };

    CliCommand getCommand(const std::string &command);

    const std::string& getCommandName(CliCommand command);
};

#endif //COOL_PROJECT_CLI_UTILS_H
