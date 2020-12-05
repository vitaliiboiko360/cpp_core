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

void ec/* error check */(int return_value, const char* msg) 
{
  if (return_value < 0)
  {
    perror(msg);
    exit(-1);
  }
}

struct buffer
{
  char data[256];
  const unsigned int size = 256;
};

struct dyn_buffer
{
  char* data;
  unsigned int size;
  unsigned int memory_size;
};

int main() 
{
  int fd;
  ec(fd = socket(AF_INET, SOCK_STREAM, 0), "socket");          
 
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr("192.168.0.103");
  server.sin_family = AF_INET;
  server.sin_port = htons(PortNumber);

  ec(connect(fd, (struct sockaddr*)&server, sizeof(server)), "connect");

  struct dyn_buffer dbuf;
  dbuf.data = (char*)malloc(256);
  dbuf.memory_size = 256;
  dbuf.size = 0;
  bool was_realloc = false;
  while(1)
  {
    printf("enter message:\n");
    int bytes_read = 0;
    int total_bytes_read = 0;
    memset(dbuf.data, 0, dbuf.size);
    do
    {
      was_realloc = false;
      ec(bytes_read = read(STDIN_FILENO, dbuf.data+dbuf.size, dbuf.memory_size-dbuf.size), "read");
      dbuf.size += bytes_read;

      if(dbuf.size == dbuf.memory_size)
      {
        was_realloc = true;
        int new_size = dbuf.memory_size * 2;
        dbuf.data = (char*)realloc((void*)dbuf.data, new_size);
        dbuf.memory_size = new_size;
      }
      
    } while(bytes_read > 0 || was_realloc);
    printf("\n\nyou entered %d characters long message\n\n", dbuf.size);
    send(fd, dbuf.data, dbuf.size, 0);


    bytes_read = 0;
    ec(bytes_read = recv(fd, dbuf.data, dbuf.memory_size, 0), "read");
    dbuf.size = bytes_read;
    printf("server replied: %.*s\n", dbuf.size, dbuf.data);
  }
  close(fd);
}