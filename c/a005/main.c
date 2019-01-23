#include <stdio.h>

float celsius_to_fahrenheit(float celsius);
float celsius_to_kelvin(float celsius);
float fahrenheit_to_celsius(float fahrenheit);

int main(int argc, char* argv[])
{

    float celsius = 0;

    while(celsius < 100)
    {
        celsius += 10;

        printf("%.2f C = %.2f F;\t = %.2f K\n",
            celsius,
            celsius_to_fahrenheit(celsius),
            celsius_to_kelvin(celsius));
    }

    return 0;
}

float celsius_to_fahrenheit(float celsius)
{
    return celsius * 9/5 + 32;
}

float celsius_to_kelvin(float celsius)
{
    return celsius + 253.15f;
}

float fahrenheit_to_celsius(float fahrenheit)
{
    return (fahrenheit+32)*5/9;
}