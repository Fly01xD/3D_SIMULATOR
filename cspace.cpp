#include "cspace.h"
#include <algorithm>

CSpace::CSpace() {}

bool CSpace::addObject(const CSpaceObject& _obj)
{
    auto i = 0;
    for(const CSpaceObject& o : objects)
    {
        if(o.getName() != _obj.getName())
            i++;
        else
            return false;
    }
    if(i == objects.size())
    {
        objects.push_back(_obj);
        return true;
    }
    else
        return false;
}

bool CSpace::removeObject(const CSpaceObject &_obj)
{
    auto it = std::find_if(objects.begin(), objects.end(),
        [&_obj](const CSpaceObject& o) {return &o == &_obj;});

    if(it == objects.end())
        return false;
    else
    {
        objects.erase(it);
        return true;
    }
}

CSpaceObject* CSpace::getObjectPointer(const std::string _name)
{
    int i = 0;
    for(CSpaceObject& o : objects)
    {
        if(o.getName() == _name)
            return &o;
    }
    return nullptr;
}

const size_t CSpace::size() const
{ return objects.size(); }
