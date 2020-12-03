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

  struct buffer buf;
  struct dyn_buffer dbuf;
  int msg_buffer_size = 1;
  char* p_msg_buffer = (char*)malloc(msg_buffer_size);
  dbuf.data = (char*)malloc(256);
  dbuf.size = 256;
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
      /* dbuf.size should not be 0 or read fails */
      ec(bytes_read = read(STDIN_FILENO, buf.data+total_bytes_read, dbuf.size-1-total_bytes_read), "read");
      total_bytes_read += bytes_read;

      if(total_bytes_read == dbuf.size-1)
      {
        was_realloc = true;
        int new_size = dbuf.size * 2;
        dbuf.data = (char*)realloc((void*)dbuf.data, new_size);
        dbuf.size = new_size;
      }
      
    } while(bytes_read > 0 || was_realloc);
    *(dbuf.data + total_bytes_read+1) = 0;
    printf("\n\nyou entered %d characters long message\n\n", total_bytes_read);
    write(fd, dbuf.data, total_bytes_read);


    ec(read(fd, buf.data, buf.size), "read");
    printf("server replied: %.*s\n", buf.size, buf.data);
  }
  close(fd);
}