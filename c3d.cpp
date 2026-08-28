#include "c3d.h"
#include <iostream>
#include <sstream>

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

CConsole *C3D::setupConsole(consoleStatus _input, consoleStatus _output)
{
    console.changeInput(_input);
    console.changeOutput(_output);
    return &console;
}

void C3D::create(objectType _type, std::vector<std::string> &_names)
{ // trzeba napisać co jeśli bool = false
    switch(_type)
    {
    case plane:
        if(!builder.buildPlane(_names))
            console.failToCreate();
        break;
    case line:
        if(!builder.buildLine(_names))
            console.failToCreate();
        break;
    case vector:
        if(!builder.buildVector(_names))
            console.failToCreate();
        break;
    case point:
        if(!builder.buildPoint(_names))
            console.failToCreate();
        break;
    default:
        console.failToCreate();
        break;
    }
}

void C3D::remove(std::vector<std::string> &_names)
{
    for(const auto &n : _names)
    {
        if(CSpaceObject* ptr = manager.searchObject(n))
        {
            if(manager.removeObject(*ptr))
                console.removed(n);
            else
                console.failToRemove(n);
        }
        else
            console.failToFind(n);
    }
}

void C3D::listAll()
{
    std::size_t s = manager.spaceSize();
    for(size_t i = 0; i < s; ++i)
    {
        std::stringstream number;
        number << i << ".\t";
        console.write(number.str());

        // można jeszcze napisać typ

        std::stringstream name;
        name << manager.objectAt(i)->getName() << "\t";
        console.write(name.str());
    }
}

