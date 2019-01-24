#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    
    char * str_1 = "aaaname of the person";
    char * str_2 = "aaagarbeage";
    printf("strcmp demo\n");
    int result;
    printf("str 1 = %s\n", str_1);
    printf("str 2 = %s\n", str_2);
    printf("strcmp(str_1, str_2) returns = %d\n", strcmp(str_1, str_2));
    printf("strcmp(str_2, str_1) returns %d\n", strcmp(str_2, str_1));
    printf("strcmp(a, b) returns %d\n", strcmp("a", "b"));
    printf("strcmp(a, c) returns %d\n", strcmp("a", "c"));
    printf("strcmp(e, d) returns %d\n", strcmp("e", "d"));
    printf("strcmp(ab, ad) returns %d\n", strcmp("ab", "ad"));
    printf("strmcp(ab, ac) returns %d\n", strcmp("ab", "ac"));
    printf("strcmp(ab, ae) returns %d\n", strcmp("ab", "ae"));
    printf("strcmp(z, b) returns %d\n", strcmp("z", "b"));
    printf("strcmp(b, z) returns %d\n", strcmp("b", "z"));

    return 0;
}

