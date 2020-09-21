

#include "server.h"
#include "client.h"

#include <iostream>

int main(int argc, char* argv[])
{   
    int j = 0; 
    char c;
    for(int i=0; i<argc; ++i)
    {
        std::cout<<argv[i]<<std::endl;
    }

    if (argc > 1 && 
        *argv[1] == '-')
    {
        if (argv[1][1] == 's')
        {
            u_server server;
            return server.run_dtgrm_srv();
        }
    }

    if (argc > 1 && 
        *argv[1] == '-')
    {
        if (argv[1][1] == 'c' && argv[1][2] == 'e')
        {
            u_client client;
            return client.run_echo_cli();
        }
        if (argv[1][1] == 'c')
        {
            u_client client;
            return client.run_dtgrm_cli();
        }
    }


    return 0;
}