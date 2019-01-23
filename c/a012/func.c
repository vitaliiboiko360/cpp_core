
#include "func.h"

#define ASIZE 256

int multiply(int a, int b)
{
    return a * b;
}

static int private_mult(int a, int b)
{
    return a / b;
}

int multiply2(int a, int b)
{
    return private_mult(a,b);
}

void print_def_size()
{
    return (void)printf("app's default array size is = %d\n", ASIZE);
}

void print_file()
{
    return (void)printf("current file is %s\n", __FILE__);
}

void func()
{
    int h = 5;
    static int k;

    printf("init var = %d\n", h++);
    printf("unint var = %d\n", k++);
}

static int volume;

void up()
{
    volume += 10;
}

void down()
{
    volume -= 10;
}

void func2()
{
    int a = 1;
    int b = 2;
}

void print_volume()
{
    printf("volume is %d\n", volume);
}