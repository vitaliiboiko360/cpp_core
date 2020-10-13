#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#include <iostream>


void chck_error_code(int ec, const char* msg)
{
    if (ec == -1)
    {
        std::cout<<msg<<"\n";
        exit(1);
    }
}

int main()
{
    const int max_conns_num = 10;
    const char* server_port = "19000";
    const int settings_number = 10;
    int settings[settings_number];

    int sfd;
    chck_error_code(
        sfd = socket(AF_INET, SOCK_STREAM, 0),
        "socket");

    chck_error_code(listen(sfd, max_conns_num), "listen");

    struct addrinfo hints;
    struct addrinfo* result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_addr = NULL;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
    chck_error_code(getaddrinfo(NULL, server_port, &hints, &result), "getaddrinfo");

    for(rp = result; rp != NULL; rp = rp->ai_next)
    {
        std::cout<<"ai_family "<<rp->ai_family<<" ";
        std::cout<<"ai_socktype "<<rp->ai_socktype<<" ";
        std::cout<<"ai_protocol "<<rp->ai_protocol<<" ";
        std::cout<<"ai_addr "<<rp->ai_addr<<"\n";
        std::cout<<"sizeof(*rp->ai_addr) "<<sizeof(*rp->ai_addr)<<"\n";
        if (rp->ai_protocol == 6)
        {
            char str[_SC_CHAR_MAX];
            inet_ntop(AF_INET6, rp->ai_addr, str, _SC_CHAR_MAX);
            std::cout<<"inet_ntop "<<str<<"\n";
        }
    }

    freeaddrinfo(result);
}