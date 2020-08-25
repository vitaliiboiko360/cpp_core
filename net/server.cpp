#include "server.h"

#include <sys/un.h>
#include <sys/socket.h>

#include <cstdio>
#include <iostream>
#include <unistd.h>

#include "error_hndl_funcs.h"

const int BUF_SIZE = 256;
const char* SOCKNAME = "/tmp/socket_a";

int u_server::run_dtgrm_srv()
{
    struct sockaddr_un srv_addr, cli_addr;
    int sfd;
    ssize_t num_bytes;
    socklen_t socket_length;

    char buffer[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        error_exit("socket");

    if(strlen(SOCKNAME) > sizeof(srv_addr.sun_path) - 1)
        error_exit("server socket path too long: %s", SOCKNAME);
    
    if(remove(SOCKNAME) == -1 && errno != ENOENT)
        error_exit("remove-%s", SOCKNAME);
    
    memset(&srv_addr, 0, sizeof(struct sockaddr_un));
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, SOCKNAME, sizeof(struct sockaddr_un) - 1);

    if (bind(sfd, (struct sockaddr*) &srv_addr, sizeof(struct sockaddr)) == -1)
    {
        error_exit("bind");
    }

    int i = 0;
    for(;;)
    {
        printf("#%d\n", i++);
        socket_length = sizeof(struct sockaddr_un);
        num_bytes = recvfrom(sfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&cli_addr, &socket_length);

        if(num_bytes == -1)
            error_exit("recvfrom");
        
        printf("Server recieved %ld bytes from %s\n", (long)num_bytes, cli_addr.sun_path);

        for (int i=0; i<num_bytes; i++)
        {
            buffer[i] = toupper((unsigned char) buffer[i]);
        }

        if(sendto(sfd, buffer, num_bytes, 0, (struct sockaddr *)&cli_addr, socket_length) != num_bytes)
            error_exit("sendto");
    }

    return 0;
}

int u_server::run_stream_server()
{
    const int BACKLOG = 5;
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
    char buffer[BUF_SIZE];
    int cfd = 0;
    int i = 0;
    for (;;)
    {
        std::cout<<"# "<<i<<"\n";
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
            error_exit("accept");
        
        while((bytes_read = read(cfd, buffer, BUF_SIZE)) > 0)
        {
            if(write(STDOUT_FILENO, buffer, bytes_read) != bytes_read)
                error_exit("partial/failed write");
        }

        if (bytes_read == -1)
            error_exit("read");

        if(close(cfd) == -1)
             error_exit("close");

        ++i;
    }
    
    return 0;
}