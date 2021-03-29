
#include <string>
#include <fstream>
#include <streambuf>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "svg_drawing.h"

namespace {

    void parse_svg(const std::string& str_svg)
    {
        xmlDocPtr doc;
        doc = xmlReadMemory(str_svg.c_str(), str_svg.size(), "svg.xml", NULL, 0);

    }
}

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