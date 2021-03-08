#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
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
    if_true_exit(socket_id == -1, "srv socket");

    unsigned char* buffer = (unsigned char*)malloc(UINT16_MAX);
    memset(buffer, 0, UINT16_MAX);
    struct sockaddr sock_addr_info;
    struct sockaddr_in src_inet_sockaddr_info, dest_inet_sockaddr_info;
    int sock_addr_info_length = sizeof(sock_addr_info);

    int bytes_received = 0;
    bytes_received = recvfrom(socket_id, buffer, UINT16_MAX, 0, &sock_addr_info, (socklen_t *)&sock_addr_info_length);
    if_true_exit(bytes_received == -1, "srv recvfrom");

    unsigned short ip_header_length;
    struct iphdr* ip_header = (struct iphdr*)(buffer);

    memset(&src_inet_sockaddr_info, 0, sizeof(src_inet_sockaddr_info));
    src_inet_sockaddr_info.sin_addr.s_addr = ip_header->saddr;
    memset(&dest_inet_sockaddr_info, 0, sizeof(dest_inet_sockaddr_info));
    dest_inet_sockaddr_info.sin_addr.s_addr = ip_header->daddr;

    printf("version: %d ", (unsigned int)ip_header->version);
    printf("internet header length: %d or %d bytes ", (unsigned int)ip_header->ihl, (unsigned int)ip_header->ihl*4);
    printf("type of service: %d ", (unsigned int)ip_header->tos);
    printf("total length: %d bytes ", ntohs(ip_header->tot_len));
    printf("identification: %d ", ntohs(ip_header->id));
    printf("time to live: %d ", ntohs(ip_header->ttl));
    printf("protocol: %d ", (unsigned int)ip_header->protocol);
    printf("header checksum: %d ", ntohs(ip_header->check));
    printf("source ip: %s ", inet_ntoa(src_inet_sockaddr_info.sin_addr));
    printf("destination ip: %s ", inet_ntoa(dest_inet_sockaddr_info.sin_addr));

    return 0;
}

int cli_main()
{
    int socket_id = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_exit(socket_id == -1, "cli socket");
    
    return 0;
}