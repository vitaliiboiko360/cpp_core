
#include <stdio.h>


int main(int argc, char* argv[])
{

    int values0[5];
    (void)values0;
    int values1[] = {1, 3, 5, 7, 9};

    printf("array of values\n");
    for(int i=0; i<5; ++i)
        printf("i=%d\tv=%d\n", i, values1[i]);

    char str[1024+1] = {'c'};
    str[1024] = '\0';
    printf("\narray of nulls\n");


    char* cursor = str;
    char ch = 'A';
    while(*cursor != '\0')
    {
        *cursor = ch++;
        cursor++;
        printf("cursor=%p\tch=%d\n", cursor, ch);
        if(ch == 'z')
            ch = 'A';
    }
        
    cursor = str;
    while(*cursor != '\0')
    {
        printf("%c", *cursor);
        cursor++;
    }
        

    printf("\n\n");
    return 0;
}
