#ifndef CBUILDER_H
#define CBUILDER_H

#include "cobjectmanager.h"
#include <vector>

class C3D;

class CBuilder
{
private:
    CObjectManager* manager;

    template<typename T>
    T* resolve(const std::string& _name);
public:
    CBuilder(CObjectManager* _m);
    ~CBuilder();

    // metody do tworzenia obiektów - true sukces, false porażka
    bool buildPlane(std::vector<std::string>& _names);
    bool buildLine(std::vector<std::string>& _names);
    bool buildVector(std::vector<std::string>& _names);
    bool buildPoint(std::vector<std::string>& _names);
};

#endif // CBUILDER_H
