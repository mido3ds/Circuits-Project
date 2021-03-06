/*      
    Element public methods source
*/
#include "Data.h"

// constructors:
Element::Element(const char &type, const int &id, const double &val) 
{
    _Constructor(type, id, val, -1);
}

// constructor for Circuit::Read() to assign the element its node_id on creation
// before testing it and adding to its node
Element::Element(const char &type, const int &id, const double &val, const int &node_id)
{
    _Constructor(type, id, val, node_id);
}

// main constructor, to be called from both overloaded constructors
void Element::_Constructor(const char &type, const int &id, const double &val, const int &node_id)
{
    _next = _prev = nullptr;
    _type = R;
    _id = -1;
    _value = 0;

    try
    {
        _SetType(type);
        _SetId(id);
        _SetValue(val);
        _SetNodeId(node_id);
    }
    catch (const error &err)
    {
        HandleError(err);
        throw err;
    }
}

// Type:
// when source transformation only
void Element::ChangeType(const char &c)
{
    _SetType(c);
}

char Element::GetType()
{
    switch (_type)
    {
        case R:
            return 'R';
        case E:
            return 'E';
        case J:
            return 'J';
        default:
            throw INVALID_STORED_TYPE;
    }
}  

// Ptr:
Element* Element::GetNext()
{
    return (_next);
}  

Element* Element::GetPrev()
{
    return (_prev);
}

// ID:
int Element::GetId()
{
    return (_id);
}

// needed for transforamtions
void Element::ChangeId(const int &num)
{
    _SetId(num);
}

// Value:
double Element::GetValue()
{
    return (_value);
}

// for transformations
void Element::ChangeValue(const double &num)
{
    _SetValue(num);
}

// retunrs address of new element wiht the same variables as this
// Note: next and prev with the returned one are NULL
Element* Element::Copy()
{
    // make new one
    Element* newElement = new Element(GetType(), _id, _value);

    return newElement;
}

// operator overloading 
// returns true if id and type are equall
bool Element::operator== (Element& e)
{
    return (_id == e.GetId() && GetType() == e.GetType());
}

bool Element::IsSame(Element* e1, Element* e2)
{
    return (*e1 == *e2);
}

// return current node id
// throws NODE_ID_IN_ELEM_UNASSIGNED if id wasn't assigned
int Element::GetNodeId()
{
    if (_node_id != -1)
        return (_node_id);
    else
        throw NODE_ID_IN_ELEM_UNASSIGNED; 
}