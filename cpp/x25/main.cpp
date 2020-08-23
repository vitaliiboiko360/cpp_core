
#include <iostream>
#include <thread>

#include "application.h"

int main(int argc, char* argv[])
{

   
    application app;
    if(app.run())
        std::cout<<"Success\n";
    else
    {
        std::cout<<"There was errors\n";
    }
    
                                                                                                                                                                                                                                                                        
    return 0;
}