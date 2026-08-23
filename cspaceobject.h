#ifndef CSPACEOBJECT_H
#define CSPACEOBJECT_H

#include <string>

class CSpaceObject
{
private:
    std::string name = "none";
public:
    CSpaceObject();
    virtual ~CSpaceObject() = default;

    virtual const std::string getName() const
        { return name; }
    virtual void changeName(const std::string _n)
        { name = _n; }
};

#endif // CSPACEOBJECT_H
