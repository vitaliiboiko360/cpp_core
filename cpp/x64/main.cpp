#include <iostream>
#include <cstring>
#include <cstdlib>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

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

int srv_main()
{
    int socket_descriptor = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_error_terminate(-1 == socket_descriptor, "socket");

    char datagram[_4KB];
    memset(datagram, 0, _4KB);

    struct iphdr *p_ip_header = (struct iphdr *) datagram;
    struct udphdr *p_udp_header = (struct udphdr *)(datagram + sizeof(struct ip));

    struct sockaddr_in inet_sock_addr;

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


    return 0;
}
int cli_main()
{

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