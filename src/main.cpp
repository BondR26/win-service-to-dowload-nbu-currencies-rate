#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <thread>
#include "win_service/service.h"
#include "cli_utils/cli_processor.h"
#include "currency_job.h"


int _tmain(int argc, _TCHAR* argv[])
{
    cli_utils::CliProcessor cli(argc, argv);

    // run as standalone
    if(cli.getCommand1() == cli_utils::CliCommand::STANDALONE)
    {
        currency_job::CurrencyMonitor monitor;

        monitor.init();

        std::thread t(&currency_job::CurrencyMonitor::do_the_job, &monitor);

        std::this_thread::sleep_for(std::chrono::seconds(120));

        monitor.stop_the_job();

        t.join();

        return EXIT_SUCCESS;
    }

    // run as service which can be registered by scm
    if(argc - 1 == 0)
    {
        SERVICE_TABLE_ENTRY DispatchTable[] =
                {
                        { SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) service::WinService::ServiceMain},
                        { NULL, NULL }
                };

        // This call returns when the service has stopped.
        // The process should simply terminate when the call returns.
        if (!StartServiceCtrlDispatcher( DispatchTable ))
        {
            int err = GetLastError();
            std::cout << (TEXT("StartServiceCtrlDispatcher"));
        }
    }
    else // run as service which can be started from command line
    {
        service::WinService service(cli.getServicePath(), cli.getCommand1());
        service.execute();
    }

    return EXIT_SUCCESS;
}