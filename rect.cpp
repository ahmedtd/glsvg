
#include "glsvg.hpp"

#include "glgeom.hpp"
using glgeom::Point2;

glsvg::Rect::Rect(const xml_node &rootnode, const weak_ptr<Elem> &parent)
:
    Elem(parent)
{
    // Check to make sure it's actually a rect
    string nodetype(rootnode.name());
    if(nodetype != "rect")
    {
        throw SvgRuntimeError("Rect::Rect() given invalid svg node type");
    }
    
    // Load the relevant attributes
    
    
    // Load any children
    for(const xml_node &child: rootnode)
    {
        mChildren.emplace_back(Elem::construct(child, weak_ptr<Elem>(this)));     
    }
}

void glsvg::Rect::draw()
{
    
}
