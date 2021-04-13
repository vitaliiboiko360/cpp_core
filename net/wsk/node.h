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


class xml_node
{
public:
    node_type type;
    std::string name;
    std::string content;
    std::map<std::string, std::string> attributes;
};