
#include "svg_model.h"
#include "svg_init_doc.h"

void svg_model::next_tick()
{
}

std::string svg_model::get_svg() const
{
    return svg_init_doc;
}