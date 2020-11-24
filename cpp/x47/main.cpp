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
const int ConversationLen = 16;
const int BuffSize = 32;

void ec/* error check */(int return_value, const char* msg) {
  perror(msg);
  if (return_value < 0)
  {
    exit(-1);
  }
}

int main() {
  int fd;
  ec(fd = socket(AF_INET, SOCK_STREAM, 0), "socket");          
 
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("192.168.0.103");
  server.sin_family = AF_INET;
  server.sin_port = htons(PortNumber);

  ec(connect(fd, (struct sockaddr*)&server, sizeof(server)), "connect");
}