
#ifndef GLSVG
#define GLSVG 

#include <deque>
using std::deque;
#include <istream>
using std::istream;
#include <stdexcept>
using std::runtime_error;

#include <boost/filesystem.hpp>
using boost::filesystem::path;
#include <boost/filesystem/fstream.hpp>
using boost::filesystem::ifstream;

#include "pugixml/pugixml.hpp"
using pugi::xml_node;

namespace glsvg
{

/// Base class for all svg document elements
class Elem
{
public:
    Elem(const weak_ptr<Elem> &parent);

    /// Draw this element to the current framebuffer
    virtual void draw();
    
    /// Compile this element to a display list
    virtual void compile(const int listid);

    /// Dispatch to the correct element constructor, based on the node
    static unique_ptr<Elem> construct(const xml_node &rootnode);

protected:
    /// The children of the given element
    deque<shared_ptr<Elem>> mChildren;

    /// The parent of the given element
    weak_ptr<Elem> mParent;
};

/// Corresponds to an <svg> element
class Svg : public Elem
{
public:

    /// Initialize this svg document from the given istream
    Svg(istream &inputstream);
    
    /// Initialize this svg document from the specified file
    Svg(const string &pathname);

    /// Initialize this svg document from the specified file
    Svg(const path &pathname);

    /// Initialize this svg document from the specified xml node
    Svg(const xml_node &rootnode, const weak_ptr<Elem> &parent);
    
    /// Draw this svg document to the current framebuffer
    virtual void draw() = 0;
};

/// Corresponds to a <rect> element
class Rect : public Elem
{
public:
    /// Initialize this rect from the given xml node
    Rect(const xml_node &rootnode, const weak_ptr<Elem> &parent);
    
    /// Draw this rect to the current framebuffer
    virtual void draw();
};
    
class SvgRuntimeError : public runtime_error
{
    SvgRuntimeError(string what);
};  
#endif
