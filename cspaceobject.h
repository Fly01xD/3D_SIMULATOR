#ifndef CSPACEOBJECT_H
#define CSPACEOBJECT_H

#include <string>
#include <memory>

class CSpaceObject
{
private:
    std::string name = "none";
public:
    CSpaceObject();
    virtual ~CSpaceObject() = default;
    virtual std::unique_ptr<CSpaceObject> clone() const = 0; // NOWE

    virtual const std::string getName() const
        { return name; }
    virtual void changeName(std::string _n)
        { name = _n; }
};

#endif // CSPACEOBJECT_H
