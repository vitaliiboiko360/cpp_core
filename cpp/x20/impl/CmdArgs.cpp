#include "CmdArgs.h"

#include <iostream>

void CmdArgs::PrintUsageToConsole()
{
    std::cout<<"Usage:\n";
    std::cout<<"\tto start server run:\n";
    std::cout<<"\t\t./application -s server_number\n";
    std::cout<<"\tto start client run:\n";
    std::cout<<"\t\t./application -c server_address server_port\n"<<std::endl;
}

void CmdArgs::PrintUsageToConsole(const char* cStrMessage)
{
    std::cout<<cStrMessage<<"\n";
    PrintUsageToConsole();
}