
#include <string>
#include <fstream>
#include <streambuf>

#include "svg_drawing.h"

u_svg_drawing::u_svg_drawing()
{
    std::ifstream file("drawing.svg");
    if(file)
    {
        file.seekg(0, std::ios::end);
        _svg.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        _svg.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
}


std::string u_svg_drawing::get_svg()
{
    return _svg;
}