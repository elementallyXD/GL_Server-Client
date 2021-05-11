#include "server.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "SERVER> Usage: ./server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;
        const unsigned int port = std::atoi(argv[1]);
        
        if (port > 0 && port < 65536) 
        {
            server s(io_context, port);
            io_context.run();
        }
        else {
            std::cerr << "SERVER> Port must be greter than 0 and less than 65536" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "SERVER> Exception: " << e.what() << "\n";
    }

    return 0;
}