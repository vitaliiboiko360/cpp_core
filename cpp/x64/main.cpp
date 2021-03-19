#include <iostream>
#include <cstring>
#include <cstdlib>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <linux/if_link.h>

const int _4KB = 4096;

void print_usage_and_exit();
void if_true_error_terminate(bool check, const char* msg);
int srv_main();
int cli_main();
unsigned short csum(unsigned short *ptr,int nbytes);

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        print_usage_and_exit();
    }

    if(0 == strcmp(argv[1], "-s"))
    {
        return srv_main();
    }

    if(0 == strcmp(argv[1], "-c"))
    {
        return cli_main();
    }

    print_usage_and_exit();
}

void print_usage_and_exit()
{
    std::cout<<"usage: ./app -s|-c\n";
    std::exit(1);
}

void if_true_error_terminate(bool check, const char* msg)
{
    if(check)
    {
        perror(msg);
        exit(1);
    }
}

void get_ip_addresses()
{
    struct ifaddrs* if_address_list;
    int family, s;
    char host[NI_MAXHOST];

    getifaddrs(&if_address_list);

    for (struct ifaddrs *ifa = if_address_list; ifa != NULL; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        /* Display interface name and family (including symbolic
            form of the latter for the common families) */

        printf("%-8s %s (%d)\n",
                ifa->ifa_name,
                (family == AF_PACKET) ? "AF_PACKET" :
                (family == AF_INET) ? "AF_INET" :
                (family == AF_INET6) ? "AF_INET6" : "???",
                family);

        /* For an AF_INET* interface address, display the address */

        if (family == AF_INET || family == AF_INET6) 
        {
            s = getnameinfo(
                ifa->ifa_addr,
                (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                host, 
                NI_MAXHOST,
                NULL, 0, NI_NUMERICHOST);

            if (s != 0) 
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                return;
            }
            printf("\t\taddress: <%s>\n", host);
        } 
        else if (family == AF_PACKET && ifa->ifa_data != NULL) 
        {
            struct rtnl_link_stats *stats = (struct rtnl_link_stats *)ifa->ifa_data;

            printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
                    "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                    stats->tx_packets, stats->rx_packets,
                    stats->tx_bytes, stats->rx_bytes);
        }
    }

    freeifaddrs(if_address_list);
}

void print_sender_ip_address(struct sockaddr_in* inet_sock_addr)
{
        printf("packet received from ");
        char address_name[UINT16_WIDTH] = "000.000.000.000";
        inet_ntop(inet_sock_addr->sin_family, (const void*)&inet_sock_addr->sin_addr, address_name, UINT16_WIDTH);
        printf("%.*s\n", UINT16_WIDTH, address_name);
}

void print_ip_and_upd_header_fields(void* buffer)
{
    printf("IP header consists : ");
    struct iphdr *ip_head = (struct iphdr *)buffer;
    struct udphdr *udp_head = (struct udphdr *) (buffer + sizeof (struct ip));
    printf("\tversion: %d ", (unsigned int)ip_head->version);
    printf("\tinternet header length: %d or %d bytes ", (unsigned int)ip_head->ihl, (unsigned int)ip_head->ihl*4);
    printf("\ttype of service: %d ", (unsigned int)ip_head->tos);
    printf("\ttotal length: %d bytes ", ntohs(ip_head->tot_len));
    printf("\tidentification: %d ", ntohs(ip_head->id));
    printf("\ttime to live: %d ", ntohs(ip_head->ttl));
    printf("\tprotocol: %d ", (unsigned int)ip_head->protocol);
    printf("\theader checksum: %x ", ntohs(ip_head->check));
    printf("\tUDP header consists : ");
    printf("\tsource port: %hd ", ntohs(udp_head->source));
    printf("\tdestination port: %hd ", ntohs(udp_head->dest));
    printf("\tupd header length: %hd ", ntohs(udp_head->len));
    printf("\tchecksum: %x \n", ntohs(udp_head->check));
}

void print_payload(void* buffer, size_t bytes_recived)
{
    printf("payload: ");
    int header_length = sizeof(struct ip) + sizeof(struct udphdr);
    char* cursor = (char*)buffer + header_length;
    int payload_length = bytes_recived - header_length; 
    for(int i=0;i<payload_length;i++)
    {
    	printf("%c", *cursor);
    	cursor++;
    }
    printf("\n");
}

void fill_ip_header(struct iphdr *p_ip_header, int payload_length)
{
    p_ip_header->ihl = 5;
	p_ip_header->version = 4;
	p_ip_header->tos = 0;
	p_ip_header->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + payload_length;
	// p_ip_header->id = htonl(54321);	// Id of this packet
	p_ip_header->id = 0;	// Id of this packet
	p_ip_header->frag_off = 0;
	p_ip_header->ttl = 255;
	p_ip_header->protocol = IPPROTO_RAW;
	p_ip_header->check = 0;	
    p_ip_header->saddr = 0; // no source ip address
    p_ip_header->daddr = 0; // no dest ip address

    p_ip_header->check = csum((unsigned short *) p_ip_header, p_ip_header->tot_len);
}

int srv_main()
{
    get_ip_addresses();

    int socket_descriptor = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_error_terminate(-1 == socket_descriptor, "socket");

    //struct udphdr *p_udp_header = (struct udphdr *)(datagram + sizeof(struct ip));

    struct sockaddr_in inet_sock_addr;
    inet_sock_addr.sin_family = AF_INET;
	inet_sock_addr.sin_port = htons(8888);
	inet_sock_addr.sin_addr.s_addr = inet_addr("192.168.129.132");


    char datagram[_4KB];
    memset(datagram, 0, _4KB);
    struct iphdr *p_ip_header = (struct iphdr *) datagram;

    // write payload
    char* payload = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(payload, "PING");

    // fill ip header
    fill_ip_header(p_ip_header, strlen(payload));

    int64_t counter = 0;
    int16_t bytes_sent = 0;
	while (1)
	{
		// send the packet
        bytes_sent = sendto(socket_descriptor, datagram, p_ip_header->tot_len,0, (struct sockaddr *)&inet_sock_addr, sizeof(inet_sock_addr));
		if(bytes_sent < 0)
		{
			perror("sendto failed");
		}
		else
		{
			printf("#%ld packet sent. length %d\n",++counter, p_ip_header->tot_len);
        }
        sleep(5);
	}

    return 0;
}

int cli_main()
{
    int socket_descriptor = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_error_terminate(-1 == socket_descriptor, "socket");

    struct sockaddr_in inet_sock_addr;
	socklen_t sock_size = sizeof(struct sockaddr_in);
	while (1)
	{
		memset(&inet_sock_addr, 0, sock_size);

		char buffer[UINT16_MAX];
		memset(buffer, 0, UINT16_MAX);
		int bytes_recv;

		bytes_recv = recvfrom (socket_descriptor, buffer, UINT16_MAX, 0, (struct sockaddr*)&inet_sock_addr, &sock_size);

		if (bytes_recv == -1)
		{
			perror("recvfrom failed");
		}
        
        int64_t counter = 0;
        int16_t bytes_sent = 0;

        bytes_sent = sendto(socket_descriptor, datagram, p_ip_header->tot_len,0, (struct sockaddr *)&inet_sock_addr, sizeof(inet_sock_addr));
		if(bytes_sent < 0)
		{
			perror("sendto failed");
		}
		else
		{
			printf("#%ld packet sent. length %d\n",++counter, p_ip_header->tot_len);
        }
	}

    return 0;
}

unsigned short csum(unsigned short *ptr,int nbytes) 
{
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum=0;
	while(nbytes>1) {
		sum+=*ptr++;
		nbytes-=2;
	}
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte)=*(u_char*)ptr;
		sum+=oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;
	
	return(answer);
}