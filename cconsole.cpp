#include "cconsole.h"
#include "c3d.h"
#include <vector>
#include <iostream>
#include "SInode.h"

CConsole::CConsole(C3D *_a) : input(on), output(on), app(_a)
{}

CConsole::~CConsole()
{}

void CConsole::Instruction()
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

void CConsole::removedSuccesfully(std::string _name)
{
    if(output == on)
        std::cout << _name << " sucessfully removed" << std::endl;
}

void CConsole::failToFind()
{
    if(output == on)
        std::cout << "Failed to find." << std::endl;
}

void CConsole::remove(std::vector<std::string> &_names)
{
    app->remove(_names);
}

void CConsole::removeAt(size_t _i)
{
    app->removeAt(_i);
}

void CConsole::clearSpace()
{
    app->clearSpace();
}

void CConsole::create(objectType _type, std::optional<std::string> _arg1, std::optional<std::string> _arg2, std::optional<std::string> _arg3, std::optional<std::string> _arg4)
{
    std::vector<std::string> arguments;
    if(_arg1)
    {
        arguments.push_back(*_arg1);
        if(_arg2)
        {
            arguments.push_back(*_arg2);
            if(_arg3)
            {
                arguments.push_back(*_arg3);
                if(_arg4)
                {
                    arguments.push_back(*_arg4);
                }
            }
        }
    }
    app->create(_type, arguments);
}

void CConsole::list(objectType _type) // trzeba napisać rozkład (numer, typ, nazwa)
{
    if(output == on)
    {
        std::cout << "NR. \t" << "Name \t" << "Type \t"
        << "X\t" << "Y\t" << "Z\t" << "X\t" << "Y\t" << "Z\t" << std::endl;
    }
    app->list(_type);
}

std::optional<std::string> CConsole::getNameAt(size_t _i)
{
    return app->getNameAt(_i-1); // w interfejsie iterujemy od 1
}

void CConsole::chooseAt(size_t _i)
{
    app->chooseAt(_i-1); // w interfejsie iterujemy od 1
}

void CConsole::choose(std::string _name)
{
    app->choose(_name);
}

SInode CConsole::chosenMod()
{
    return app->chosenMod();
}

SInode CConsole::chosenInfo()
{
    return app->chosenInfo();
}

SInode CConsole::chosenCrossProduct(std::string _name)
{
    return app->chosenCrossProduct(_name);
}

SInode CConsole::chosenDotProduct(std::string _name)
{
    return app->chosenDotProduct(_name);
}

void CConsole::unchoose()
{
    app->clearChosen();
}

void CConsole::save()
{
    std::optional<std::string> n = std::nullopt;
    app->saveStash(n);
}

void CConsole::save(std::string _name)
{
    std::optional<std::string> n = _name;
    app->saveStash(n);
}

void CConsole::write(std::string _text)
{
    if(output == on)
        std::cout << _text;
}

void CConsole::writeInode(SInode _info)
{
    if(output == on)
    {
        switch(_info.type)
        {
        case plane:
            std::cout << "plane" << "\t";
            break;
        case line:
            std::cout << "line" << "\t";
            break;
        case vector:
            std::cout << "vector" << "\t";
            break;
        case point:
            std::cout << "point" << "\t";
            break;
        case unknown:
            std::cout << "unknown" << "\t";
            break;
        case all:
            std::cout << "-----" << "\t";
        }

        size_t s = _info.values.size();
        if(_info.type != all)
        {
            for(size_t i = 0; i < s; ++i)
            {
                std::cout << _info.values[i] << "\t";
            }
        }
        std::cout << std::endl;
    }
}