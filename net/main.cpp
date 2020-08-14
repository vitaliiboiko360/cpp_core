

#include "server.h"

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
            return server.run();
        }
    }

    return 0;
}