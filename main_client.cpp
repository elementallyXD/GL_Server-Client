#include "client.h"

#include <cli/cli.h>
#include <cli/clifilesession.h>

#include <boost/algorithm/string.hpp> // split
#include <boost/lexical_cast.hpp>     // lexical_cast

using namespace cli;

int main(void)
{
    client client;
    bool connected = false;
    auto rootMenu = std::make_unique< Menu >("CLIENT");

    rootMenu->Insert(
        "connect",
        [&](std::ostream& out, const std::string& host_port)
        {
            if (!host_port.empty())
            {
                try
                {
                    std::vector<std::string> result_vect;
                    boost::split(result_vect, host_port, boost::is_any_of(":"));

                    if (result_vect.size() == 2)
                    {
                        int port = boost::lexical_cast<int>(result_vect[1].c_str());
                        if (port > 0 && port < 65536)
                        {
                            client.ConnectToServer(
                                result_vect[0],    // host
                                result_vect[1]     // port
                            );
                            connected = true;
                        }
                        else
                        {
                            std::cout << "\tUNABLE TO CONNECT\n" << std::endl;
                            throw std::runtime_error("\tError: Invalid Port. Port must be greter than 0 and less than 65536\n");
                        }
                    }
                    else
                    {
                        out << "\tConnect string wrong! Use: \"connect <string>\"" << std::endl;
                    }
                }
                catch (const std::exception& ex)
                {
                    out << "CLIENT> Connect exception: " << ex.what() << "\n";
                }
            }
            else
            {
                out << "\tConnect string must be not empty! Use: \"connect <string>\"" << std::endl;
            }
        },
        "Connect to Server");

    rootMenu->Insert(
        "send",
        [&client, &connected](std::ostream& out, const std::vector<std::string>& msg)
        {
            if (msg.size() > 0)
            {
                try
                {
                    if (connected) {
                        client.Send(msg);
                        client.GetReply();
                    }
                    else {
                        out << "\tYou need to connect to the server! Use: \"connect <string>\"" << "\n";
                    }
                }
                catch (const std::exception& ex)
                {
                    out << "CLIENT> Send exception: " << ex.what() << "\n";
                }
            }
            else
            {
                out << "\tMessage string must be not empty! Use: \"send <string>\"" << std::endl;
            }
        },
        "Send message");

    Cli cli(std::move(rootMenu));
    cli.ExitAction([](auto& out)
        {
            out << "\tEXIT. Goodbye!\n";
        });

    CliFileSession input(cli);
    input.Start();

    return 0;
}
