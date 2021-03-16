#include <iostream>
#include <cstring>
#include <cstdlib>

void print_usage_and_exit();
int srv_main();
int cli_main();

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        print_usage_and_exit();
    }

    if(0 == strcmp(argv[1], "-s"))
    {
        return srv_main();
    }

    if(0 == strcmp(argv[1], "-c"))
    {
        return cli_main();
    }

    print_usage_and_exit();
}


void print_usage_and_exit()
{
    std::cout<<"usage: ./app -s|-c\n";
    std::exit(1);
}

int srv_main()
{

    return 0;
}
int cli_main()
{

    return 0;
}