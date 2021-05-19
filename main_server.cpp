#include "server.h"

#include <cli/cli.h>
#include <cli/clifilesession.h>

#include <boost/thread.hpp>

using namespace cli;

int main(void)
{
    boost::asio::io_service io_service;
    unsigned int port;
    bool set_port = false, started = false;
    std::unique_ptr<server> ser;
    
    boost::thread run_service;

    auto rootMenu = std::make_unique< Menu >("SERVER");
    rootMenu->Insert(
        "start",
        [&](std::ostream& out)
        {
            if (set_port && !started)
            {
                try
                {
                    started = true;
                    ser = std::make_unique<server>(std::move(io_service), port);

                    std::cout << "\tSERVER STARTED ON " << port << std::endl;

                    run_service = boost::thread([&io_service]
                        {
                                io_service.reset();
                                io_service.run();
                        });
                }
                catch (const std::exception& e)
                {
                    std::cerr << "\tSERVER> Exception: " << e.what() << "\n";
                }
            }
            else {
                out << "\tYou already started the server or you must set the port for the server. Use: \"setPort <int>\" or \"start\"" << "\n";
            }
        },
        "Start server");

    rootMenu->Insert(
        "setPort",
        [&port, &set_port](std::ostream& out, const int& x)
        {
            if (x > 0 && x < 65536)
            {
                port = x;
                out << "\tSERVER ON PORT: " << port << std::endl;
                set_port = true;
            }
            else
            {
                out << "\tPort must be greter than 0 and less than 65536" << std::endl;
            }
        },
        "Set port for server");

    rootMenu->Insert(
        "stop",
        [&](std::ostream& out)
        {
            if (set_port) {
                try
                {
                    if (!io_service.stopped())
                        io_service.stop();
                    run_service.join();

                    delete ser.release();
                    ser.reset();

                    started = false;
                    out << "\tSTOPED ON PORT " << port << std::endl;
                }
                catch (const std::exception& e)
                {
                    std::cerr << "\tSERVER> Exception: " << e.what() << "\n";
                }
            }
            else {
                out << "You don't specify the port or don't start the server." << "\n";
            }
        },
        "Stop server");

    Cli cli(std::move(rootMenu));
    cli.ExitAction([&io_service, &run_service, &ser, &started](auto& out)
        {
            
            if (!io_service.stopped())
                io_service.stop();
                
            run_service.join();

            delete ser.release();
            ser.reset();

            started = false;
            out << "\tEXIT. Goodbye!\n";
        });

    CliFileSession input(cli);
    input.Start();

    return 0;
}
