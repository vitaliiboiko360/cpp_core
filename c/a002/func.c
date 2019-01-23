#include <stdio.h>


static int apples;

void oranges_set(int n)
{
    apples = n;
}

int oranges_get()
{
    return apples;
}

void apples_set(int n)
{
    apples = n;
}

int apples_get()
{
    return apples;
}

void hello()
{
    printf("hello from separate src file\n");
}