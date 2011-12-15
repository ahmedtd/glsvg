
#include "glsvg.hpp"

#include "pugixml/pugixml.hpp"
using pugi::xml_document;

glsvg::Elem::Elem(const weak_ptr<Elem> &parent)
:
    mParent(parent)
{
}

// Compile this element to a display list
void glsvg::Elem::compile(const int listid)
{
    
}

// Dispatch to the correct element constructor, based on the node
unique_ptr<Elem> glsvg::Elem::construct(
    const xml_node &rootnode,
    const weak_ptr<Elem> &parent)
{
    string nodetype(rootnode.name());
    
    if(nodetype == "svg")
        return shared_ptr<Elem>(new Svg(rootnode, parent));
    else if(nodetype == "rect")
        return shared_ptr<Elem>(new Rect(rootnode, parent));
    else
        throw SvgRuntimeError("Elem::construct() given invalid node type");
}

glsvg::Svg::Svg(const string &pathname)
:
    Svg(path(pathname))
{
}

glsvg::Svg::Svg(const path &pathname)
:
    Svg(istream(pathname))
{
}

glsvg::Svg::Svg(istream &inputstream)
{
    xml_document svgdoc;
    svgdoc.load(inputstream);
    Svg(svgdoc, nullptr);
}

glsvg::Svg::Svg(const xml_node &rootnode, const weak_ptr &parent)
:
    Elem(parent)
{
    // Check that the node is an <svg> node
    string nodetype(rootnode.name());
    if(nodetype != "svg")
        throw SvgRuntimeError("Svg::Svg() given invalid xml node type");

    // Parse relevant attributes

    // Generate this element's children
    for(const xml_node &child: rootnode)
    {
        mChildren.emplace_back(Elem::construct(child, weak_ptr<Elem>(this)));
    }
}

void glsvg::Svg::draw()
{
    // The root svg type does no drawing of its own, only draws its children
    for(const shared_ptr<Elem> &childptr: mChildren)
    {
        childptr->draw();
    }
}

glsvg::SvgRuntimeError::SvgRuntimeError(string what)
:
    runtime_error(what)
{
}

