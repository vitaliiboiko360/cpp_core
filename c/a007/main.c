#include <stdio.h>

#include "func.h"

int main(int argc, char* argv[])
{
    int var1, var2, var3 = 0;
    var1 = 0;
    var2 = 1;
    var3 = 1;

    printf("\ntest\nfibonacci(%d, %d, %d):\n", var1, var2, var3);
    fibonacci(var1, var2, var3);
    printf("\n");

    printf("\ntest\nfibonnaci2(%d, %d, %d):\n", var1, var2, var3);
    fibonacci2(var1, var2, var3);
    printf("\n");

    return 0;
}