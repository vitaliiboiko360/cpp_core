#include <stdio.h>
#include "func.h"
#include "func2.h"


int main(void)
{
    typedef unsigned char uint8_t;
    typedef signed char int8_t;
    

    uint8_t array1[10];
    int8_t array2[10];
    (void)array1;
    (void)array2;

    hello();

    int apples = 4;
    int oranges = apples;

    apples = 3;

    printf("apples=%d\n", apples);
    printf("oranges=%d\n", oranges);

    printf("\n");

    apples_set(21);
    printf("global apples=%d\n", apples_get());
    printf("unknown apples=%d\n", apples);

    oranges_set(420);
    printf("call to apples_get results in = %d\n", apples_get());

    printf("\n\n***\n\n");
    printf("apples_get=%d\toranges_get=%d\n\n\n", apples_get(), oranges_get());

    printf("before apples_set(33)\n\n");
    printf("apples_get=%d\tapples_get_2=%d\n\n", apples_get(), apples_get_2());
    apples_set(33);
    printf("after\n\n");
    printf("apples_get=%d\tapples_get_2=%d\n\n", apples_get(), apples_get_2());

    return 0;
}