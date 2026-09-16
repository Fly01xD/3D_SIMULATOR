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

    CSpace(const CSpace&)            = delete;
    CSpace& operator=(const CSpace&) = delete;
    CSpace(CSpace&&)                 = default;
    CSpace& operator=(CSpace&&)      = default;

    bool addObject(const CSpaceObject& _obj);
    bool removeObject(const CSpaceObject& _obj);
    CSpaceObject* getObjectPointer(const std::string _name);
    CSpaceObject* getObjectPointerAt(const size_t _i);
    const size_t size() const;
    void clear();
};

#endif // CSPACE_H
