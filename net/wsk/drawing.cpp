
#include <string>
#include <fstream>
#include <streambuf>

#include "drawing.h"

drawing::drawing()
{
    std::ifstream file("drawing.svg");
    if(file)
    {
        file.seekg(0, std::ios::end);
        _drawing_string.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        _drawing_string.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
}


std::string drawing::get_drawing()
{
    return _drawing_string;
}