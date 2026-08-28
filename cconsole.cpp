#include "cconsole.h"
#include "c3d.h"
#include <vector>
#include <iostream>

CConsole::CConsole(C3D *_a) : input(on), output(on), app(_a)
{}

CConsole::~CConsole()
{}

void CConsole::getInstruction()
{}

void CConsole::failToCreate()
{
    if(output == on)
        std::cout << "Failed to create an object." << std::endl;
}

void CConsole::failToRemove(std::string _name)
{
    if(output == on)
        std::cout << "Failed to remove " << _name << "." << std::endl;
}

void CConsole::removed(std::string _name)
{
    if(output == on)
        std::cout << _name << " sucessfully removed" << std::endl;
}

void CConsole::failToFind(std::string _name)
{
    if(output == on)
        std::cout << "Failed to find " << _name << "." << std::endl;
}

void CConsole::remove(std::vector<std::string> &_names)
{
    app->remove(_names);
}

void CConsole::create(objectType _type, std::optional<std::string> _name1, std::optional<std::string> _name2, std::optional<std::string> _name3, std::optional<std::string> _name4)
{
    std::vector<std::string> names;
    if(_name1)
    {
        names.push_back(*_name1);
        if(_name2)
        {
            names.push_back(*_name2);
            if(_name3)
            {
                names.push_back(*_name3);
                if(_name4)
                {
                    names.push_back(*_name4);
                }
            }
        }
    }
    app->create(_type, names);
}
