
#include <string>

#include "node.h"

class u_svg_drawing
{
public:
    u_svg_drawing();
    std::string get_svg();

// private:
    std::string _svg;
    std::vector<node> _nodes;
};