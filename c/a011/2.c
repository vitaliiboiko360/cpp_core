#include <stdio.h>

int main()
{
    char * str1 = "Hello string";
    char str2[] = "another swell string";
    printf("using %%s format %s\n", str1);
    printf("passing array %s\n", str2);
    return 0;
}