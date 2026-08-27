#include "cbuilder.h"
#include "cpoint.h"

#include <sstream>

CBuilder::CBuilder(CObjectManager* _m) : manager(_m)
{}

bool CBuilder::buildPlane(std::vector<std::string> &_names)
{

}

bool CBuilder::buildLine(std::vector<std::string> &_names)
{

}

bool CBuilder::buildVector(std::vector<std::string> &_names)
{

}

bool CBuilder::buildPoint(std::vector<std::string> &_names)
{
    size_t s = _names.size();
    switch (s) {
    case 4: { // trzy liczby i nazwa
        float a[3] = {0};
        for(size_t i = 0; i < _names.size() - 1; ++i) {
            std::stringstream ss(_names[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CPoint newObject(a[0], a[1], a[2]);
        manager->addObject(newObject, &_names[3]);
        return true;
        break;
    }
    case 3: { // trzy liczby
        float a[3] = {0};
        for(size_t i = 0; i < _names.size() - 1; ++i) {
            std::stringstream ss(_names[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CPoint newObject(a[0], a[1], a[2]);
        manager->addObject(newObject, nullptr);
        return true;
        break;
    }
    default:
        return false;
        break;
    }
}

template<typename T>
T *CBuilder::resolve(const std::string &_name)
{
    CSpaceObject* obj = manager->searchObject(_name);
    if(!obj) return nullptr;
    return dynamic_cast<T*>(obj);
}