#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <cstdlib>

void if_true_exit(bool check, const char* msg)
{
    if(check)
    {
        std::cout<<msg<<std::endl;
        std::exit(1);
    }
}

int cli_main();
int srv_main();

int main(int argc, char* argv[])
{



}

int cli_main()
{
    int socket_id = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if_true_exit(socket_id == -1, "cli socket");
    
}

int srv_main()
{

}