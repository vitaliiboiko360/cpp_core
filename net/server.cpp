#include "server.h"

#include <sys/un.h>
#include <sys/socket.h>

#include <cstdio>
#include <iostream>
#include <unistd.h>

#include "error_hndl_funcs.h"

int u_server::run()
{
    const char *SOCKNAME = "/tmp/socket_a";

    int sfd;

    struct sockaddr_un addr;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1)
    {
        error_exit("socket");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKNAME, sizeof(addr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
    {
        std::cout<<"errno= "<<errno<<"\n";
        if (errno == EADDRINUSE)
        {
            std::cout<<"address \""<<SOCKNAME<<"\" in use\n";   
            unlink(SOCKNAME);
        }
        if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
        {
            error_exit("bind");
        }
    }

    std::cout<<"bind called\n";
    getc(stdin);

    return 0;
}