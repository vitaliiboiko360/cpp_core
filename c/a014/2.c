#include <stdio.h>

typedef struct
{
    short first;
    int second;
    short third;
} Layout;

typedef struct
{
    short first;
    short second;
    int third;
} Layout1;

typedef union 
{
    short s;
    int i;
} BigInt;

int main()
{

    Layout l;

    printf("short %ld\n", sizeof(l.first));
    printf("int %ld\n", sizeof(l.second));
    printf("whole struct %ld\n", sizeof(l));

    Layout1 l1;

    printf("short1 %ld\n", sizeof(l1.first));
    printf("int1 %ld\n", sizeof(l1.second));
    printf("whole struct1 %ld\n", sizeof(l1));

}