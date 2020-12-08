#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>


int ec /* error check */(int return_value, char* msg)
{
    if (return_value < 0)
    {
        std::cerr<<msg<<std::endl;
        exit(1);
    }
    return return_value;
}

class client
{
public:
    int run() 
    {
        return 0;
    }
};

class server
{
public:
    int run() 
    {
        int srv_fd = ec(socket(AF_INET, SOCK_STREAM, 0), "socket");

        struct sockaddr_in srv_addr;
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        srv_addr.sin_port = htons(1122);

        ec(bind(srv_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)), "bind");



        return 0;
    }
};