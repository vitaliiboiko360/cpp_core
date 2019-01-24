#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RAND_STR_MAX_SIZE 10

void compare_strings(char * str_1, char * str_2);
int give_rand_string(int n_chars, char * str_output);

int main(int argc, char** argv)
{
    char str_1[RAND_STR_MAX_SIZE];
    char str_2[RAND_STR_MAX_SIZE];
    for(int i=0; i<10; ++i)
    {
        give_rand_string(RAND_STR_MAX_SIZE-5, str_1);
        give_rand_string(RAND_STR_MAX_SIZE-5, str_2);
        compare_strings(str_1, str_2);
    }
        
    return 0;
}

void compare_strings(char * str_1, char * str_2)
{
    printf("strcmp(%s, %s) = %d\n", str_1, str_2, strcmp(str_1, str_2));
}

int give_rand_string(int n_chars, char * str_output)
{
    if (n_chars < 1)
        n_chars = 1;
    else if(n_chars >= RAND_STR_MAX_SIZE)
        n_chars = RAND_STR_MAX_SIZE-1;
    
    int count = 0;
    for(int i=0; i<n_chars; ++i)
    {
        int c = (rand()%3)+97;
        count += sprintf(str_output, "%c", c);
        ++str_output;
    }
    return count;
}