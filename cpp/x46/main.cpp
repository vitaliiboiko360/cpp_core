#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

const int PortNumber = 15000;
const int MaxConnects = 5;
const int BuffSize = 32;

void report(const char* msg, int terminate) 
{
  perror(msg);
  if (terminate) exit(-1); 
}

int main() 
{
  int fd = socket(AF_INET, SOCK_STREAM, 0);          
  if (fd < 0) report("socket", 1); 

  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));          
  saddr.sin_family = AF_INET;                
  saddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  saddr.sin_port = htons(PortNumber);        

  if (bind(fd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)
    report("bind", 1); 
  
  if (listen(fd, MaxConnects) < 0) 
    report("listen", 1); 

  fprintf(stderr, "Listening on port %i for clients...\n", PortNumber);
  char* str_addr = inet_ntoa(saddr.sin_addr);
  fprintf(stdout, "addr %s\n", str_addr);
  
  while (1) 
  {
    struct sockaddr_in caddr; 
    int len = sizeof(caddr);  

    int client_fd = accept(fd, (struct sockaddr*) &caddr, (socklen_t*)&len);  
    if (client_fd < 0) 
    {
      report("accept", 0); 
      continue;
    }

    int iter_count = 0;
    while (1) 
    {
      char buffer[BuffSize + 1];
      memset(buffer, '\0', sizeof(buffer));
      int count = read(client_fd, buffer, sizeof(buffer));
      if (count > 0) 
      {
        puts(buffer);
        write(client_fd, buffer, sizeof(buffer)); 
      }
      else
      {
        break;
      }
      printf("#%d\n", iter_count++);
    }
    printf("closing socket\n");
    close(client_fd); 
  }  
  return 0;
}