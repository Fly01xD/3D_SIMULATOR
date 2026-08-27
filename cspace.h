#ifndef CSPACE_H
#define CSPACE_H

#include "cspaceobject.h"

#include <vector>
class CSpaceObject;

// przestrzeń, w której przechowywane są obiekty matematyczne
class CSpace
{
    std::vector<std::unique_ptr<CSpaceObject>> objects;
public:
    CSpace();
    ~CSpace();

    bool addObject(const CSpaceObject& _obj);
    bool removeObject(const CSpaceObject& _obj);
    CSpaceObject* getObjectPointer(const std::string _name);
    const size_t size() const;
};

#endif // CSPACE_H
