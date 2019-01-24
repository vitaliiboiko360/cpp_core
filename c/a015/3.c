#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    
    char * str_test_numbers = "42 32 1 2  0x1d1d1d1d 10101101";
    char * next = str_test_numbers;
    int n_str = strlen(str_test_numbers);
    int limit = 0;
    printf("str_test_numbers+n_str = %p\n", str_test_numbers+n_str);
    while(next != str_test_numbers+n_str)
    {
        printf("parsed value %ld\n", strtol(next, &next, 0));
        printf("strtol sets \"next\" pointer to %p\n", next);
        if(limit++>10)
        {
            printf("we hit break\n");
            break;
        }
    }

    return 0;
}

