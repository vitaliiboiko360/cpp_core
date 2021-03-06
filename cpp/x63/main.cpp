/*
	Raw UDP sockets
*/
#include<stdio.h>	//for printf
#include<string.h> //memset
#include<sys/socket.h>	//for socket ofcourse
#include<stdlib.h> //for exit(0);
#include<errno.h> //For errno - the error number
#include<netinet/udp.h>	//Provides declarations for udp header
#include<netinet/ip.h>	//Provides declarations for ip header
#include <arpa/inet.h>
#include <unistd.h>

/* 
	96 bit (12 bytes) pseudo header needed for udp header checksum calculation 
*/
struct pseudo_header
{
	u_int32_t source_address;
	u_int32_t dest_address;
	u_int8_t placeholder;
	u_int8_t protocol;
	u_int16_t udp_length;
};

/*
	Generic checksum calculation function
*/
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

int main (void)
{
	//Create a raw socket of type IPPROTO
	int s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
	
	if(s == -1)
	{
		//socket creation failed, may be because of non-root privileges
		perror("Failed to create raw socket");
		exit(1);
	}
	
	//Datagram to represent the packet
	char datagram[4096] , source_ip[32] , *data , *pseudogram;
	
	//zero out the packet buffer
	memset (datagram, 0, 4096);
	
	//IP header
	struct iphdr *iph = (struct iphdr *) datagram;
	
	//UDP header
	struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));
	
	struct sockaddr_in sin;
	struct pseudo_header psh;
	
	//Data part
	data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
	strcpy(data , "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	
	//some address resolution
	strcpy(source_ip , "192.168.129.132");
	
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.s_addr = inet_addr("192.168.129.132");
	
	//Fill in the IP Header
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + strlen(data);
	iph->id = htonl (54321);	//Id of this packet
	iph->frag_off = 0;
	iph->ttl = 255;
	iph->protocol = IPPROTO_RAW;
	iph->check = 0;		//Set to 0 before calculating checksum
	iph->saddr = inet_addr ( source_ip );	//Spoof the source ip address
	iph->daddr = sin.sin_addr.s_addr;
	
	//Ip checksum
	iph->check = csum ((unsigned short *) datagram, iph->tot_len);
	
	//UDP header
	udph->source = htons (8622);
	udph->dest = htons (6666);
	udph->len = htons(8 + strlen(data));	//tcp header size
	udph->check = 0;	//leave checksum 0 now, filled later by pseudo header
	
	//Now the UDP checksum using the pseudo header
	psh.source_address = inet_addr( source_ip );
	psh.dest_address = sin.sin_addr.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_RAW;
	psh.udp_length = htons(sizeof(struct udphdr) + strlen(data) );
	
	int psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + strlen(data);
	pseudogram = (char*)malloc(psize);
	
	memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
	memcpy(pseudogram + sizeof(struct pseudo_header) , udph , sizeof(struct udphdr) + strlen(data));
	
	udph->check = csum( (unsigned short*) pseudogram , psize);
	
	struct sockaddr_in sock_addr_info;
	socklen_t sock_size = sizeof(struct sockaddr_in);
	while (1)
	{
		memset(&sock_addr_info, 0, sock_size);

		char buffer[UINT16_MAX];
		memset(buffer, 0, UINT16_MAX);
		int bytes_recv;
		//printf("before call to recvfrom\n");
		//bytes_recv = recvfrom (s, buffer, UINT16_MAX, 0, (struct sockaddr *) &sin, (socklen_t*)sizeof (sin));
		bytes_recv = recvfrom (s, buffer, UINT16_MAX, 0, (struct sockaddr*)&sock_addr_info, &sock_size);
		//Recv the packet
		if (bytes_recv == -1)
		{
			perror("recvfrom failed");
		}
		//Data recv successfully
		else
		{
			
			printf("Packet Received from ");
			char address_name[UINT16_WIDTH] = "000.000.000.000";
			inet_ntop(sock_addr_info.sin_family, (const void*)&sock_addr_info.sin_addr, address_name, UINT16_WIDTH);
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
