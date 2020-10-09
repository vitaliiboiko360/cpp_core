#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{

    const int server_port = 19000;
    const int settings_number = 10;
    int settings[settings_number];

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1)
    {
        printf("socket");
        exit(1);
    }

    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(server_port);
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&srv_addr, 0, sizeof(struct sockaddr_in));
    int ec = bind(sfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if (ec == -1)
    {
        printf("socket");
        exit(1);
    }
    close(sfd);
}