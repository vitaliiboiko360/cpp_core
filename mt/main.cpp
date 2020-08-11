#include <fstream>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{

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
}