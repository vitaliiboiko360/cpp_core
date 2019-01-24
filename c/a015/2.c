#include <stdio.h>
#include <ctype.h>

int print_usage_exit();

int main(int argc, char** argv)
{
    if(argc < 2)
        return print_usage_exit();
    
    printf("the name of the file in uppercase\n");
    char * p_str_arg = 0;
    p_str_arg = argv[0];
    while(*p_str_arg)
    {
        putchar(toupper(*p_str_arg++));
    }
    putchar('\n');
    for(int i=1; i<argc; ++i)
    {
        printf("print argument #%d:\n", i);
        p_str_arg = argv[i];
        while(*p_str_arg)
        {
            putchar(toupper(*p_str_arg++));
        }
        putchar('\n');
    }
    
    return 0;
}

int print_usage_exit()
{
    printf("suply more command line arguments\n");
    printf("at least 2 arguments are enough\n");
    return 1;
}