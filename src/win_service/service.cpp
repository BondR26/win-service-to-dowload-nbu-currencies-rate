//
// Created by 26bon on 2/14/2024.
//
#include "service.h"
#include "currency_job.h"

#include <windows.h>
#include <cstdio>
#include <iostream>
#include <map>
#include <thread>


namespace service {

    SERVICE_STATUS g_ServiceStatus;
    SERVICE_STATUS_HANDLE g_ServiceStatusHandle;
    HANDLE                g_StopEvent = NULL;

    VOID ReportSvcStatus( DWORD dwCurrentState,
                          DWORD dwWin32ExitCode,
                          DWORD dwWaitHint)
    {
        static DWORD dwCheckPoint = 1;

        // Fill in the SERVICE_STATUS structure.

        g_ServiceStatus.dwCurrentState = dwCurrentState;
        g_ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
        g_ServiceStatus.dwWaitHint = dwWaitHint;

        if (dwCurrentState == SERVICE_START_PENDING)
            g_ServiceStatus.dwControlsAccepted = 0;
        else g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;

        if ( (dwCurrentState == SERVICE_RUNNING) ||
             (dwCurrentState == SERVICE_STOPPED) )
            g_ServiceStatus.dwCheckPoint = 0;
        else g_ServiceStatus.dwCheckPoint = dwCheckPoint++;

        // Report the status of the service to the SCM.
        SetServiceStatus( g_ServiceStatusHandle, &g_ServiceStatus );
    }


    class Params
    {
    public:
        Params(const std::string &service_path_)
                : service_path(service_path_)
        {
        }

        std::string service_path;
    };

    class WinServiceCommand
    {
    public:
        virtual void init(const Params& params_) = 0;

        virtual int execute() = 0;

        virtual ~WinServiceCommand() = default;
    };

    class InstallCommand : public WinServiceCommand {
    public:

        void init(const Params& params_) override
        {
            _service_path = params_.service_path;
        }

        int execute() override
        {
            SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
            if (!hSCManager) {
                std::cout << "Error: Can't open Service Control Manager" << std::endl;
                return -1;
            }

            SC_HANDLE hService = CreateService(
                    hSCManager,
                    SERVICE_NAME,
                    SERVICE_NAME,
                    SERVICE_ALL_ACCESS,
                    SERVICE_WIN32_OWN_PROCESS,
                    SERVICE_DEMAND_START,
                    SERVICE_ERROR_NORMAL,
                    _service_path.c_str(),
                    NULL, NULL, NULL, NULL, NULL
            );

            if (!hService) {
                int err = GetLastError();
                switch (err) {
                    case ERROR_ACCESS_DENIED:
                        std::cout << "Error: ERROR_ACCESS_DENIED" << std::endl;
                        break;
                    case ERROR_CIRCULAR_DEPENDENCY:
                        std::cout << "Error: ERROR_CIRCULAR_DEPENDENCY" << std::endl;
                        break;
                    case ERROR_DUPLICATE_SERVICE_NAME:
                        std::cout << "Error: ERROR_DUPLICATE_SERVICE_NAME" << std::endl;
                        break;
                    case ERROR_INVALID_HANDLE:
                        std::cout << "Error: ERROR_INVALID_HANDLE" << std::endl;
                        break;
                    case ERROR_INVALID_NAME:
                        std::cout << "Error: ERROR_INVALID_NAME" << std::endl;
                        break;
                    case ERROR_INVALID_PARAMETER:
                        std::cout << "Error: ERROR_INVALID_PARAMETER" << std::endl;
                        break;
                    case ERROR_INVALID_SERVICE_ACCOUNT:
                        std::cout << "Error: ERROR_INVALID_SERVICE_ACCOUNT" << std::endl;
                        break;
                    case ERROR_SERVICE_EXISTS:
                        std::cout << "Error: ERROR_SERVICE_EXISTS" << std::endl;
                        break;
                    default:
                        std::cout << "Error: Undefined" << std::endl;
                }
                CloseServiceHandle(hSCManager);
                return -1;
            }

            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            std::cout << "Success install service!" << std::endl;
            return 0;
        }

    private:
        std::string _service_path;
    };

    class RemoveCommand : public WinServiceCommand {
    public:

        void init(const Params& params_) override
        {
        }

        int execute() override {
            SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
            if (!hSCManager) {
                std::cout << "Error: Can't open Service Control Manager" << std::endl;
                return -1;
            }
            SC_HANDLE hService = OpenService(hSCManager, SERVICE_NAME, SERVICE_STOP | DELETE);
            if (!hService) {
                std::cout << "Error: Can't remove service" << std::endl;
                CloseServiceHandle(hSCManager);
                return -1;
            }

            DeleteService(hService);
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            std::cout << "Success remove service!" << std::endl;
            return 0;
        }
    };

    class StartCommand : public WinServiceCommand {
    public:

        void init(const Params& params_) override {
        }

        int execute() override
        {
            SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
            SC_HANDLE hService = OpenService(hSCManager, SERVICE_NAME, SERVICE_START);

            if (!StartService(hService, 0, NULL))
            {
                int err = GetLastError();
                CloseServiceHandle(hSCManager);
                std::cout << "Error: Can't start service" << std::endl;
                return -1;
            }

            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return 0;
        }
    };

    class StopCommand : public WinServiceCommand {
    public:
        void init(const Params& params_) override {
        }

        int execute() override {
            SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
            SC_HANDLE hService = OpenService(hSCManager, SERVICE_NAME, SERVICE_STOP);
            SERVICE_STATUS status;
            if (!ControlService(hService, SERVICE_CONTROL_STOP, &status)) {
                CloseServiceHandle(hSCManager);
                std::cout << "Error: Can't stop service" << std::endl;
                return -1;
            }

            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return 0;
        }
    };

    class FactoryInterface {
    public:
        FactoryInterface() = default;

        virtual ~FactoryInterface() = default;

        virtual std::unique_ptr<WinServiceCommand> create() = 0;
    };

    template<typename T>
    class WinServiceCommandFactory : public FactoryInterface {
    public:
        WinServiceCommandFactory() = default;

        ~WinServiceCommandFactory() = default;

        std::unique_ptr<WinServiceCommand> create() override {
            return std::make_unique<T>();
        }
    };


    const std::map<cli_utils::CliCommand, std::shared_ptr<FactoryInterface>> gWinServiceCommands =
            {
                    {cli_utils::CliCommand::INSTALL, std::make_shared<WinServiceCommandFactory<InstallCommand>>()},
                    {cli_utils::CliCommand::REMOVE,  std::make_shared<WinServiceCommandFactory<RemoveCommand>>()},
                    {cli_utils::CliCommand::START,   std::make_shared<WinServiceCommandFactory<StartCommand>>()},
                    {cli_utils::CliCommand::STOP,    std::make_shared<WinServiceCommandFactory<StopCommand>>()}
            };


    void WinService::ControlHandler(DWORD request)
    {
        switch (request)
        {
            case SERVICE_CONTROL_STOP:
                std::cout << "Stopped." << std::endl;

                ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
                SetEvent(g_StopEvent);
                ReportSvcStatus(g_ServiceStatus.dwCurrentState, NO_ERROR, 0);
                return;

            case SERVICE_CONTROL_SHUTDOWN:
                std::cout << "Shutdown." << std::endl;

                g_ServiceStatus.dwWin32ExitCode = 0;
                g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
                SetServiceStatus(g_ServiceStatusHandle, &g_ServiceStatus);
                return;

            default:
                break;
        }

        SetServiceStatus(g_ServiceStatusHandle, &g_ServiceStatus);

        return;
    }

    void WINAPI WinService::ServiceMain(int argc, char *argv[])
    {
        g_ServiceStatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, (LPHANDLER_FUNCTION) ControlHandler);
        if (! g_ServiceStatusHandle)
        {
            auto err = GetLastError();
            return;
        }

        int error;
        int i = 0;

        ZeroMemory (&g_ServiceStatus, sizeof(g_ServiceStatus));
        g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
        g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
        g_ServiceStatus.dwWin32ExitCode = 0;
        g_ServiceStatus.dwServiceSpecificExitCode = 0;
        g_ServiceStatus.dwCheckPoint = 0;
        g_ServiceStatus.dwWaitHint = 0;


        g_StopEvent = CreateEvent(
                NULL,    // default security attributes
                TRUE,    // manual reset event
                FALSE,   // not signaled
                NULL);   // no name

        if ( g_StopEvent == NULL)
        {
            ReportSvcStatus( SERVICE_STOPPED, GetLastError(), 0 );
            return;
        }

        // Report running status when initialization is complete.

        ReportSvcStatus( SERVICE_RUNNING, NO_ERROR, 0 );

        // TO_DO: Perform work until service stops.
        //createthread(main_cycle);

        while(1)
        {

            currency_job::CurrencyMonitor monitor;
            monitor.init();
            std::thread t(&currency_job::CurrencyMonitor::do_the_job, &monitor);

            //Check whether to stop the service.
            WaitForSingleObject(g_StopEvent, INFINITE);

            monitor.stop_the_job();
            t.join();

            ReportSvcStatus( SERVICE_STOPPED, NO_ERROR, 0 );
            return;
        }

        return;
    }

    WinService::WinService(const std::string &service_path_, cli_utils::CliCommand command_)
            : _service_path(service_path_)
    {
        auto command = gWinServiceCommands.at(command_)->create();

        command->init(Params(_service_path));

        _command = std::move(command);

    }

    WinService::~WinService() {
    }

    int WinService::execute()
    {
        return _command->execute();
    }
}