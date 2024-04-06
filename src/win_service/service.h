//
// Created by 26bon on 2/14/2024.
//

#ifndef COOL_PROJECT_SERVICE_H
#define COOL_PROJECT_SERVICE_H
#include <Windows.h>
#include <string>
#include <memory>
#include "cli_utils/cli_utils.h"

#define SERVICE_NAME "CoolProjectService"

namespace service {

    class WinServiceCommand;

    class WinService
    {
    public:

        WinService(const std::string &service_path_, cli_utils::CliCommand command_);

        ~WinService();

        int execute();

        static void WINAPI ControlHandler(DWORD request);

        static void WINAPI ServiceMain(int argc, char **argv);

        //DWORD WINAPI ServiceWorkerThread(LPVOID lpParam);

    private:

        std::unique_ptr<WinServiceCommand> _command;
        std::string _service_path;

    };

    int my_main();

};

#endif //COOL_PROJECT_SERVICE_H
