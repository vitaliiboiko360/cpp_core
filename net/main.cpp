

#include "server.h"

#include <iostream>

int main(int argc, char* argv[])
{   
    int j = 0; 
    char c;
    for(int i=0; i<argc; ++i)
    {
        while ((c = argv[i][j++]) != 0)
        {
            std::cout<<c;
        }
        std::cout<<std::endl;
    }

    if (argc > 0 && 
        *argv[0] == '-')
    {
        if (argv[0][1] == 's')
        {
            u_server server;
            return server.run();
        }
    }

    return 0;
}