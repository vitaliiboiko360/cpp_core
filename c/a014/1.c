typedef struct Pixel
{
    float x;
    float y;
} Pixel;

typedef unsigned char byte;

typedef struct Color
{
    byte Red;
    byte Green;
    byte Blue;
} Color;

int main()
{

    Pixel p1;
    Color c1;

    Color c2 = { 10.0f, 12.0f };
}