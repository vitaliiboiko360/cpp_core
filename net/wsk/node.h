#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>

enum node_type
{
    none = 0,
    svg,
    group,
    polyline,
    text
};

struct node
{
    node_type type;
    std::string name;
    std::string content;
    std::map<std::string, std::string> attributes;
};

#endif // NODE_H