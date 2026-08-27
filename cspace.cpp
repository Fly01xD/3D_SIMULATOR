#include "cspace.h"
#include <algorithm>

CSpace::CSpace() {}

CSpace::~CSpace()
{}

bool CSpace::addObject(const CSpaceObject& _obj)
{
    for(const auto& o : objects)
        if(o->getName() == _obj.getName())
            return false;
    objects.push_back(_obj.clone());
    return true;
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
    for(auto& o : objects)
        if(o->getName() == _name)
            return o.get(); // stabilny adres — obiekt jest na stercie, wektor przenosi tylko wskaźniki
    return nullptr;
}

const size_t CSpace::size() const
{ return objects.size(); }
