#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "svg_drawing.h"

namespace {

    void print_xml_elements(xmlNode *element_to_start)
    {
        if(!element_to_start)
            return;

        xmlNode *cur_node = NULL;
        for(cur_node = element_to_start; cur_node; cur_node = cur_node->next)
        {
            if(cur_node->type == XML_ELEMENT_NODE)
            {
                std::cout<<"name: "<<cur_node->name<<std::endl;
            }
        }
        print_xml_elements(element_to_start->children);
    }

    void print_xml_elements_attributes(xmlNode *element_to_start)
    {
        if(!element_to_start)
            return;

        xmlNode *cur_node = NULL;
        for(cur_node = element_to_start; cur_node; cur_node = cur_node->next)
        {

            if(cur_node->type == XML_ELEMENT_NODE)
            {
                std::cout<<"tag \""<<cur_node->name<<"\""<<std::endl;

                xmlAttr* attribute = cur_node->properties;
                while(attribute)
                {
                xmlChar* value = xmlNodeListGetRawString(cur_node->doc, attribute->children, 1);
                std::cout<<"\tattribute \""<<attribute->name<<"\"=\""<<(char*)attribute->children<<"\""<<std::endl;
                xmlFree(value); 
                attribute = attribute->next;
                }
            }
        }
        print_xml_elements_attributes(element_to_start->children);
    }

    void print_svg(const std::string& str_svg)
    {
        xmlDocPtr doc;
        doc = xmlReadMemory(str_svg.c_str(), str_svg.size(), "svg.xml", NULL, 0);
        if(!doc)
        {
            return;
        }
        
        xmlNode *root_element = xmlDocGetRootElement(doc);

        print_xml_elements_attributes(root_element);
    }

    void parse_svg(const std::string& str_svg)
    {
        xmlDocPtr doc;
    }
}

u_svg_drawing::u_svg_drawing()
{
    std::ifstream file("drawing.svg");
    if(!file)
        return;
    
    file.seekg(0, std::ios::end);
    _svg.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    _svg.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    
    print_svg(_svg);
}


std::string u_svg_drawing::get_svg()
{
    return _svg;
}