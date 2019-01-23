
#include <stdio.h>
typedef double(*ptr_to_dbl_func)(double temperature);
double celsius_to_fahrenheit(double temperature);

double convert_by(double value, ptr_to_dbl_func ptr_to_func);

int main(int argc, char* argv[])
{
    double f=25.5;
    printf("f=%f\n",f);
    printf("celsius_to_fahrenheit(f)=%f\n", 
        celsius_to_fahrenheit(f));

    printf("demo pointers to functions\n");
    
    

    printf("using pointer to conversion function\n");
    printf("convert_by(f,func)\t=%f\n", convert_by(f, celsius_to_fahrenheit));


}

double celsius_to_fahrenheit(double temperature)
{
    return temperature * 9/5 + 32;
}

double convert_by(double value, ptr_to_dbl_func ptr_to_func)
{
    return ptr_to_func(value);
}