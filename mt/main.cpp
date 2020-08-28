#include <fstream>
#include <iostream>
#include <cstdlib>
#include <thread>

int main(int argc, char* argv[])
{
    auto create_file = []{
        std::ofstream file("file");

        for (int i=0; i<100; ++i)
        {
            file << std::rand() << " ";
            
            
            if ((i%10==0) && i!=0)
            {
                file << '\n';
                std::cout << file.tellp() << "\n";
            }
        }
        std::cout << file.tellp() << "\n";
    };
    
    std::cout<<"before thread\n";
    std::thread l_thread{create_file};

    std::cout<<"after thread\n";
    l_thread.join();
}