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
    const int BACKLOG = 5;
    const int BUF_SZ = 256;

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
    
    if (listen(sfd, BACKLOG) == -1)
        error_exit("listen");

   
    ssize_t bytes_read;
    char buffer[BUF_SZ];
    int cfd = 0;
    for (;;)
    {
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
            error_exit("accept");
        
        while((bytes_read = read(cfd, buffer, BUF_SZ)) > 0)
        {
            if(write(STDOUT_FILENO, buffer, bytes_read) != bytes_read)
                error_exit("partial/failed write");
            
            if (bytes_read == -1)
                error_exit("read");

            if(close(cfd) == -1)
                error_exit("close");
        }
    }
    
    return 0;
}