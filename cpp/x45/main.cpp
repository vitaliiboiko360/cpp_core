#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int ns,s;
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    unsigned short port = (unsigned short) atoi(argv[1]);
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(2);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port   = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind()");
        exit(3);
    }

    if (listen(s, 1) != 0)
    {
        perror("Listen()");
        exit(4);
    }

    struct sockaddr_in client;
    int namelen = sizeof(client);
    if ((ns = accept(s, (struct sockaddr *)&client, (socklen_t *)&namelen)) == -1)
    {
        perror("Accept()");
        exit(5);
    }

    char buf[12];
    if (recv(ns, buf, sizeof(buf), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }

    if (send(ns, buf, sizeof(buf), 0) < 0)
    {
        perror("Send()");
        exit(7);
    }

    close(ns);
    close(s);

    printf("Server ended successfully\n");
    exit(0);
}