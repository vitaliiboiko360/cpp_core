#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

struct udp_header {
    unsigned short int uh_sport;
    unsigned short int uh_dport;
    unsigned short int uh_len;
    unsigned short int uh_check;
}; 

void if_true_exit(bool check, const char* msg)
{
    if(check)
    {
        perror(msg);
        std::exit(1);
    }
}

void print_usage_exit()
{
    std::cout<<"usage: app -c|-s\n";
    std::exit(1);
}

int srv_main();
int cli_main();

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        print_usage_exit();
    }

    if(0 == strcmp(argv[1], "-s"))
    {
        return srv_main();
    }
    else if(0 == strcmp(argv[1], "-c"))
    {
        return cli_main();
    }
    else
    {
        print_usage_exit();
    }
}

int srv_main()
{
    int socket_id = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_exit(socket_id == -1, "cli socket");

    return 0;
}

int cli_main()
{
    int socket_id = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_exit(socket_id == -1, "cli socket");
    
    return 0;
}