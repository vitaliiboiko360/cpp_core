#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <map>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "svg_drawing.h"
#include "node.h"

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
                xmlChar* value = xmlNodeListGetString(cur_node->doc, attribute->children, 1);
                std::cout<<"\tattribute \""<<attribute->name<<"\"=\""<<value<<"\""<<std::endl;
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
    
    std::vector<node> parse_svg(const std::string& str_svg)
    {

        std::vector<node> results;
        xmlDocPtr doc;
        doc = xmlReadMemory(str_svg.c_str(), str_svg.size(), "svg.xml", NULL, 0);
        
        if(!doc)
        {
            std::cout<<"error parsing doc=nullptr\n";
            return {};
        }

        xmlNode *root_element = xmlDocGetRootElement(doc);

        xmlNode *outer_node = NULL;
        xmlNode *inner_node = NULL;
        outer_node = root_element;   
        int current_layer = 0;
        while(outer_node)
        {
            inner_node = outer_node;
            while(inner_node)
            {
                if(inner_node->type == XML_ELEMENT_NODE)
                {
                    node nd;
                    std::cout<<"assing\n";
                    nd.name.assign((char*)inner_node->name);
                    std::cout<<"assing\n";
                    if(inner_node->content)
                    {
                        nd.content.assign((char*)inner_node->content);
                    }

                    xmlAttr* attribute = inner_node->properties;
                    while(attribute)
                    {
                        xmlChar* value = xmlNodeListGetString(inner_node->doc, attribute->children, 1);
                        
                        std::string key{(char*)attribute->name};
                        std::cout<<"map[]\n";
                        nd.attributes[key] = {(char*)value};

                        xmlFree(value); 
                        attribute = attribute->next;
                    }

                    results.push_back(nd);
                }
                inner_node = inner_node->next;

            }
            current_layer++;
            outer_node = outer_node->children;
        }

        return results;
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
    
    _nodes = parse_svg(_svg);
}


std::string u_svg_drawing::get_svg()
{
    return _svg;
}