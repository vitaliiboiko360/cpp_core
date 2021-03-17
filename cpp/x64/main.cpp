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
    getifaddrs();
}

int srv_main()
{
    int socket_descriptor = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_error_terminate(-1 == socket_descriptor, "socket");

    char datagram[_4KB];
    memset(datagram, 0, _4KB);

    struct iphdr *p_ip_header = (struct iphdr *) datagram;
    //struct udphdr *p_udp_header = (struct udphdr *)(datagram + sizeof(struct ip));

    struct sockaddr_in inet_sock_addr;
    inet_sock_addr.sin_family = AF_INET;
	inet_sock_addr.sin_port = htons(8888);
	inet_sock_addr.sin_addr.s_addr = inet_addr("192.168.129.132");

    // write payload
    char* payload = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(payload, "PING");

    // fill in the IP header
	p_ip_header->ihl = 5;
	p_ip_header->version = 4;
	p_ip_header->tos = 0;
	p_ip_header->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(payload);
	p_ip_header->id = htonl(54321);	// Id of this packet
	p_ip_header->frag_off = 0;
	p_ip_header->ttl = 255;
	p_ip_header->protocol = IPPROTO_RAW;
	p_ip_header->check = 0;	
    p_ip_header->saddr = 0; // no source ip address
    p_ip_header->daddr = 0; // no dest ip address

    p_ip_header->check = csum((unsigned short *) datagram, p_ip_header->tot_len);

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
		else
		{
			
			printf("Packet Received from ");
			char address_name[UINT16_WIDTH] = "000.000.000.000";
			inet_ntop(inet_sock_addr.sin_family, (const void*)&inet_sock_addr.sin_addr, address_name, UINT16_WIDTH);
			printf("%.*s", UINT16_WIDTH, address_name);
			printf(" : ");

			printf(" IP header consists : ");
			struct iphdr *ip_head = (struct iphdr *)buffer;
			struct udphdr *udp_head = (struct udphdr *) (buffer + sizeof (struct ip));
			printf("\nversion: %d ", (unsigned int)ip_head->version);
			printf("\ninternet header length: %d or %d bytes ", (unsigned int)ip_head->ihl, (unsigned int)ip_head->ihl*4);
			printf("\ntype of service: %d ", (unsigned int)ip_head->tos);
			printf("\ntotal length: %d bytes ", ntohs(ip_head->tot_len));
			printf("\nidentification: %d ", ntohs(ip_head->id));
			printf("\ntime to live: %d ", ntohs(ip_head->ttl));
			printf("\nprotocol: %d ", (unsigned int)ip_head->protocol);
			printf("\nheader checksum: %x ", ntohs(ip_head->check));
			printf("\nUDP header consists : ");
			printf("\nsource port: %hd ", ntohs(udp_head->source));
			printf("\ndestination port: %hd ", ntohs(udp_head->dest));
			printf("\nupd header length: %hd ", ntohs(udp_head->len));
			printf("\nchecksum: %x ", ntohs(udp_head->check));

			printf("\npayload: ");
			int header_length = sizeof(struct ip) + sizeof(struct udphdr);
			char* cursor = buffer + header_length;
			int payload_length = bytes_recv - header_length; 
			for(int i=0;i<payload_length;i++)
			{
				printf("%c", *cursor);
				cursor++;
			}
			printf("\n");
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