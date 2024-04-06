//
// Created by 26bon on 2/14/2024.
//

#include "cli_utils.h"
#include <string>
#include <map>

namespace cli_utils {
    const std::map<std::string, CliCommand> gCliCommands =
            {
                    {"install", CliCommand::INSTALL},
                    {"remove",  CliCommand::REMOVE},
                    {"start",   CliCommand::START},
                    {"stop",    CliCommand::STOP},
                    {"standalone", CliCommand::STANDALONE},
                    {"none",    CliCommand::NONE}
            };

    CliCommand getCommand(const std::string &command)
    {
        auto it = gCliCommands.find(command);
        if (it != gCliCommands.end()) {
            return it->second;
        }
        return CliCommand::NONE;
    }

    const std::string& getCommandName(CliCommand command)
    {
        for (auto it = gCliCommands.begin(); it != gCliCommands.end(); ++it)
        {
            if (it->second == command)
            {
                return it->first;
            }
        }
        return "NONE";
    }
}