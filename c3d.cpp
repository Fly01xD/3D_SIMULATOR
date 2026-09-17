#include "c3d.h"
#include <iostream>
#include <sstream>

SInode C3D::returnNullInode()
{
    SInode inode;
    inode.type = unknown;
    console.writeInode(inode);
    return inode;
}

C3D::C3D() : space(), manager(&space), console(this), builder(&manager)
{}

C3D::~C3D()
{}

CConsole *C3D::setupConsole(consoleStatus _input, consoleStatus _output)
{
    console.changeInput(_input);
    console.changeOutput(_output);
    return &console;
}

void C3D::create(objectType _type, std::vector<std::string> &_arguments)
{
    switch(_type)
    {
    case plane:
        if(!builder.buildPlane(_arguments))
            console.failToCreate();
        break;
    case line:
        if(!builder.buildLine(_arguments))
            console.failToCreate();
        break;
    case vector:
        if(!builder.buildVector(_arguments))
            console.failToCreate();
        break;
    case point:
        if(!builder.buildPoint(_arguments))
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
                console.removedSuccesfully(n);
            else
                console.failToRemove(n);
        }
        else
            console.failToFind();
    }
}

void C3D::removeAt(size_t _i)
{
    if(CSpaceObject* tmp = manager.objectAt(_i))
    {
        std::stringstream name;
        name << "index " << _i;
        if(manager.removeObject(*manager.objectAt(_i)))
            console.removedSuccesfully(name.str());
        else
            console.failToRemove(name.str());
    }
    else
        console.failToFind();
}

void C3D::clearSpace()
{
    manager.clearSpace();
}

std::optional<std::string> C3D::getNameAt(size_t _i)
{
    if(CSpaceObject* tmp = manager.objectAt(_i))
        return tmp->getName();
    else
        return std::nullopt;
}

std::vector<SInode> C3D::list(objectType _type)
{
    std::size_t s = manager.spaceSize();
    std::vector<SInode> table;
    for(size_t i = 0; i < s; ++i)
    {
        CSpaceObject* tmp = manager.objectAt(i);
        CReader tmpReader(tmp);
        SInode info = tmpReader.getInode();
        if(info.type == _type || _type == all)
        {
            std::stringstream number;
            number << i+1 << ".\t";
            console.write(number.str());

            std::stringstream name;
            name << tmp->getName() << "\t";
            console.write(name.str());

            table.push_back(info);
            console.writeInode(info);
        }
    }
    return table;
}

void C3D::choose(std::string _name)
{
    if(CSpaceObject* ptr = manager.searchObject(_name))
        reader.changeObject(ptr);
    else
        console.failToFind();
}

void C3D::chooseAt(size_t _i)
{
    if(CSpaceObject* tmp = manager.objectAt(_i))
        reader.changeObject(tmp);
    else
        console.failToFind();
}

SInode C3D::chosenMod()
{
    if(reader.readyToRead())
    {
        reader.readModulus();
        console.writeInode(reader.getInode());
        return reader.getInode();
    }
    else
    {
        return returnNullInode();
    }
}

SInode C3D::chosenInfo()
{
    if(reader.readyToRead())
    {
        reader.readObject();
        console.writeInode(reader.getInode());
        return reader.getInode();
    }
    else
    {
        return returnNullInode();
    }
}

SInode C3D::chosenCrossProduct(std::string _name)
{
    if(CSpaceObject* obj = manager.searchObject(_name))
    {
        if(!reader.readyToRead())
            return returnNullInode();
        if(!reader.readCrossProduct(obj))
            return returnNullInode();
        console.writeInode(reader.getInode());
        return reader.getInode();
    }
    else
        return returnNullInode();
}

SInode C3D::chosenDotProduct(std::string _name)
{
    if(CSpaceObject* obj = manager.searchObject(_name))
    {
        if(!reader.readyToRead())
            return returnNullInode();
        if(!reader.readDotProduct(obj))
            return returnNullInode();
        console.writeInode(reader.getInode());
        return reader.getInode();
    }
    else
        return returnNullInode();
}

void C3D::clearChosen()
{
    reader.changeObject(nullptr);
}

void C3D::saveStash(std::optional<std::string> _name) // problem z rzutowaniem w dół
{
    if(reader.getStash())
    {
        if(_name)
            manager.addObject(*reader.getStash(), *_name);
        else
            manager.addObject(*reader.getStash(), std::nullopt);
    }
    reader.clearStash();
}

