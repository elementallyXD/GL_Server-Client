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

        /*HELP*/

        boost::asio::io_context io_context;
        
        /*SET PORT*/
        const unsigned int port = std::atoi(argv[1]);
        
        if (port > 0 && port < 65536) 
        {
            std::cout << "SERVER> ON PORT: " << port << std::endl;
            
            /*START*/
            server s(io_context, port);
            std::cout << "SERVER> STARTED ON " << port << std::endl;
            io_context.run();

            ///*STOP*/
            //io_context.stop();
            //std::cout << "SERVER> STOPED ON PORT " << port << std::endl;

            //EXIT
            //io_context.stop();
            //std::cout << "SERVER> EXIT << std::endl;
            //return 0;
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
