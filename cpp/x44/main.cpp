
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

void ec /* error check */ (int status, const char* msg)
{
    if (status != 0)
    {
        fprintf(stderr, "%s\n", msg);
        exit(1);
    }
}

int main()
{
    struct sockaddr_storage cli_addr;
    struct addrinfo hints;
    struct addrinfo* p_serv_info;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    ec(getaddrinfo(NULL, "15000", &hints, &p_serv_info), "getaddrinfo");

    char ip_addres[INET6_ADDRSTRLEN];
    void* addr;
    const char* ip_version;
    for(struct addrinfo* p = p_serv_info; p != NULL; p = p->ai_next)
    {
        if(p->ai_family == AF_INET)
        {
            ip_version = "IPv4";
        }
        else // IPv6
        {
            ip_version = "IPv6";
        }
        inet_ntop(p->ai_family, &addr, ip_addres, sizeof(ip_addres));
        printf("%s %s\n", ip_version, ip_addres);
    }

}