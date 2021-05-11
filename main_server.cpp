#include "server.h"

#include <cli/cli.h>
#include <cli/clifilesession.h>

using namespace cli;

int main(void)
{
    try
    {
        boost::asio::io_context io_context;
        unsigned int port;
        bool set_port = false;
        
        auto rootMenu = std::make_unique< Menu >("SERVER");
        rootMenu->Insert(
            "start",
            [&](std::ostream& out) 
            { 
                if (set_port) 
                {
                    server s(io_context, port);
                    std::cout << "\tSERVER STARTED ON " << port << std::endl;
                    if(io_context.stopped())
                        io_context.restart();
                    io_context.run();
                }
                else {
                    out << "You must set port for server. Use: \"setPort <value>\"" << "\n";
                }
            },
            "Start server");
        
        rootMenu->Insert(
            "setPort",
            [&port, &set_port](std::ostream& out, int x) 
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
                if (set_port){
                    if (!io_context.stopped())
                        io_context.stop();
                    out << "\tSTOPED ON PORT " << port << std::endl;
                }
                else {
                    out << "You don't specify the port or don't start the server." << "\n";
                }
            },
            "Stop server");

        Cli cli(std::move(rootMenu));
        cli.ExitAction([&io_context](auto& out) 
        { 
            if (!io_context.stopped())
                io_context.stop();
               
            out << "\tEXIT. Goodbye!\n"; 
        });

        CliFileSession input(cli);
        input.Start();
    }
    catch (std::exception& e)
    {
        std::cerr << "SERVER> Exception: " << e.what() << "\n";
    }

    return 0;
}
