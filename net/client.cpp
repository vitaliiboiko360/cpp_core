
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include "client.h"
#include "error_hndl_funcs.h"

const int BUF_SZ = 256;
const char* socket_path = "/tmp/socket_a";

int u_client::run_echo_cli()
{
    char buffer[BUF_SZ];
    int num_bytes;
    for(;;)
    {
        num_bytes = read(STDIN_FILENO, buffer, BUF_SZ);
        if (num_bytes == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        num_bytes = write(STDOUT_FILENO, buffer, num_bytes);
        if (num_bytes == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
}

int u_client::run_dtgrm_cli()
{
    struct sockaddr_un srv_addr, cli_addr;

    int sfd;
    size_t message_length;
    ssize_t num_bytes;

    char buffer[BUF_SZ];

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sfd == -1)
        error_exit("socket");

    memset(&cli_addr, 0, sizeof(struct sockaddr_un));
    cli_addr.sun_family = AF_UNIX;
    snprintf(cli_addr.sun_path, sizeof(struct sockaddr_un)-1, "%s_%ld", socket_path, (long)getpid());

    if(bind(sfd, (struct sockaddr *) &cli_addr, sizeof(struct sockaddr_un)) == -1)
        error_exit("bind");

    /* get server address */
    memset(&srv_addr, 0, sizeof(struct sockaddr_un));
    srv_addr.sun_family = AF_UNIX;
    strncpy(srv_addr.sun_path, socket_path, sizeof(struct sockaddr_un));

    int i=0;
    for (;;)
    {
        if((num_bytes = read(STDIN_FILENO, buffer, BUF_SZ)) == -1)
            error_exit("read");
        
        if(sendto(sfd, buffer, num_bytes, 0, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr_un)) != num_bytes)
            error_exit("sendto");

        num_bytes = recvfrom(sfd, buffer, BUF_SZ, 0, NULL, NULL);
        if (num_bytes == -1)
            error_exit("recvfrom");
        
        printf("Response %d : %.*s\n", ++i, (int)num_bytes, buffer);
    }


    return 0;
}

int u_client::run_stream_cli()
{
    struct sockaddr_un addr;

    int sfd = 0;
    ssize_t bytes_read;
    
    char buffer[BUF_SZ];
    

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        error_exit("socket");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

    if(connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
        error_exit("connect");
    
    int i = 0;
    while(true)
    {
        //td::cout<<i<<" doing read\n";
        bytes_read = read(STDIN_FILENO, buffer, BUF_SZ);
        //std::cout<<i<<" doing write\n";
        if (-1 == write(sfd, buffer, bytes_read))
            perror("");
        // if (write(sfd, buffer, bytes_read) != bytes_read)
        //     error_exit("partial/failed write");
        ++i;
    }

    if (bytes_read == -1)
        error_exit("read");
    
    std::cout<<"\nend\n"<<i++<<"\n";

    return 0;
}