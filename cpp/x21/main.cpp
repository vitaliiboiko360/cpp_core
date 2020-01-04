#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include "Node.h"

int main(int argc, char* argv[])
{
    pid_t tChildPid;
    switch(tChildPid = fork())
    {
        case -1:
        {
            std::cout<<"fork returned -1"<<std::endl;
            exit(1);
        }
        case 0:
            StartNode();
        default:
        {
            std::cout<<"node process is started\n";
            std::cout<<"pid = "<<tChildPid<<"\n";
            std::cout<<"parent process simulates some hardwork by printing a dot into console every two seconds:\n";
            int nStatus{0};
            int nReturn{0};
            while(true)
            {
                std::cout<<" . ";
                std::cout.flush();
                sleep(2);
                nReturn = waitpid(tChildPid, &nStatus, WNOHANG);
                if(nReturn != 0)
                    break;
            }
            if(nReturn == tChildPid)
                std::cout<<"child process terminated with a status "<<nStatus<<std::endl;
            if(nReturn < 0)
                std::cout<<"child process terminated with some error:\nDEBUG IT"<<std::endl;
        }
    }


    return 0;
}