#include <stdio.h>
#include <errno.h>

int main()
{
    FILE * f = NULL;
    
    f = fopen("test.txt", "w");
    if(f == 0)
    {
        perror("fopen_s");
    }

    fclose(f);
    return 0;
}