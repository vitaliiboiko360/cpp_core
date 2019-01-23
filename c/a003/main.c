#include <stdio.h>

const char* print_bool(int n)
{
    if (n != 0)
        return "True";
    else
        return "False";
}

char* to_binary(int n)
{
    static const int int_size = 32;
    static char ret[32+1];
    for(int i=0; i<int_size; ++i)
    {
    }
    return ret;
}

int main(int argc, char* argv[])
{

    int a = 16;
    int b = 2;


    // arithmetics operators
    // printf("a=%d\tb=%d\na%%b=%d\n\n", a, b, a%b);
    // printf("a=%d\tb=%d\na/b=%d\n\n", a, b, a/b);

    // printf("5 - 4 + 3 = %d\n", 5 - 4 + 3);
    // printf("(5 - 4) + 3 = %d\n", (5 - 4) + 3);

    // printf("5 - (4 + 3) = %d\n", 5 - (4 + 3));

    // printf("5 * 4 + 3 = %d\n", 5 * 4 + 3);
    // printf("5 * (4 + 3) = %d\n", 5 * (4 + 3));


    // // relational operators

    // printf("a < b = %s\n", print_bool(a < b));
    // printf("a > b = %s\n", print_bool(a > b));
    // printf("a <= b = %s\n", print_bool(a <= b));
    // printf("a >= b = %s\n", print_bool(a >= b));
    // printf("a == b = %s\n", print_bool(a == b));
    // printf("a != b = %s\n", print_bool(a != b));

    // printf("5 + 4 < 10 = %d\n", (5 + 4 < 10));
    // printf("(5 + 4) < 10 = %d\n", ((5 + 4) < 10));
    // printf("5 + (4 < 10) = %d\n", 5 + (4 < 10));

    // printf("0 || 1 && (0 || 1) = %d\n", 0 || 1 && (0 || 1));

    printf("a=%d in hex:\t%x\n", a, a);
    printf("b=%d in hex:\t%x\n", b, b);
    printf("%d&%d<< in hex:\t%x\n", a, b, a&b);

    for(int i=0; i<257; ++i)
    {
        printf("i=%d\tin hex:\t%x\n",i,i);
    }

    return 0;
}