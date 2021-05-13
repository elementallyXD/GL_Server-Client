#include "server.h"

#include <cli/cli.h>
#include <cli/clifilesession.h>

#include <boost/thread.hpp>

using namespace cli;

int main(void)
{
    boost::asio::io_service io_service;
    unsigned int port;
    bool set_port = false;

    auto rootMenu = std::make_unique< Menu >("SERVER");
    rootMenu->Insert(
        "start",
        [&](std::ostream& out)
        {
            if (set_port)
            {
                try
                {
                    server s(std::move(io_service), port);
                    std::cout << "\tSERVER STARTED ON " << port << std::endl;

                    if (io_service.stopped())
                        io_service.restart();
                        
                    std::thread run_service([&] { io_service.run(); });
                    run_service.join();

                }
                catch (const std::exception& e)
                {
                    std::cerr << "SERVER> Exception: " << e.what() << "\n";
                }
            }
            else {
                out << "You must set port for server. Use: \"setPort <int>\"" << "\n";
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
                    out << "\tSTOPED ON PORT " << port << std::endl;
                }
                catch (const std::exception& e)
                {
                    std::cerr << "SERVER> Exception: " << e.what() << "\n";
                }
            }
            else {
                out << "You don't specify the port or don't start the server." << "\n";
            }
        },
        "Stop server");

    Cli cli(std::move(rootMenu));
    cli.ExitAction([&io_service](auto& out)
        {
            if (!io_service.stopped())
                io_service.stop();

            out << "\tEXIT. Goodbye!\n";
        });

    CliFileSession input(cli);
    input.Start();

    return 0;
}
