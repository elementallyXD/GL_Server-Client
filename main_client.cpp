#include "client.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "CLIENT> Usage: ./client <host> <port>\n";
            return 1;
        }

        /*HELP*/

        /*CONNECT TO SERVER*/
        client client;
        client.ConnectToServer(
            argv[1],    // host
            argv[2]     // port
        );

        /*SEND*/
        client.Send();
        client.GetReply();

        /*EXIT*/
        //return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "CLIENT> Exception: " << e.what() << "\n";
    }

    return 0;
}