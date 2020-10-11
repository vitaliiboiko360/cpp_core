#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    const int server_port = 19000;
    const int settings_number = 10;
    int settings[settings_number];

    int sfd;
    chck_error_code(
        sfd = socket(AF_INET, SOCK_STREAM, 0),
        "socket");

    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(server_port);

    inet_pton(AF_INET, "0.0.0.0", &srv_addr.sin_addr.s_addr);

    chck_error_code(
        bind(sfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)),
        "bind");

    chck_error_code(listen(sfd, max_conns_num), "listen");

    close(sfd);
}