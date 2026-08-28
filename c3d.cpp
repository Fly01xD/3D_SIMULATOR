#include "c3d.h"
#include <iostream>

C3D::C3D() : space(), manager(&space), console(this), builder(&manager)
{
    if(Setup())
    {
        std::cout << "3D sucessfully initialized." << std::endl;
        console.getInstruction();
    }
    else
        std::cout << "Failed to initialize 3D." << std::endl;
}

C3D::~C3D()
{}

bool C3D::Setup()
{
    space = CSpace();
    manager = CObjectManager(&space);
    console = CConsole(this);
    builder = CBuilder(&manager);
    return true;
}

void C3D::create(objectType _type, std::vector<std::string> &_names)
{ // trzeba napisać co jeśli bool = false
    switch(_type)
    {
    case plane:
        if(!builder.buildPlane(_names))
            console.failToCreate();
    case line:
        if(!builder.buildLine(_names))
            console.failToCreate();
    case vector:
        if(!builder.buildVector(_names))
            console.failToCreate();
    case point:
        if(!builder.buildPoint(_names))
            console.failToCreate();
    default:
        console.failToCreate();
    }
}

