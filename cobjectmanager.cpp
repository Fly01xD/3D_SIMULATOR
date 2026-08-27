#include "cobjectmanager.h"
#include "CSpace.h"
#include "cline.h"
#include "cplane.h"
#include <iostream>

CObjectManager::CObjectManager(CSpace* _s) : space(_s), alert(on), nPlane(0), nLine(0), nVector(0), nPoint(0) {}

CObjectManager::~CObjectManager()
{}

void CObjectManager::addObject(CSpaceObject &_obj,const std::string *_name)
{
    if(_name)
        _obj.changeName(*_name);
    else
    {
        if(CPlane* p = dynamic_cast<CPlane*>(&_obj))
        {
            nPlane++;
            std::string type = "plane";
            type += std::to_string(nPlane);
            _obj.changeName(type);
        }
        if(CLine* l = dynamic_cast<CLine*>(&_obj))
        {
            nLine++;
            std::string type = "line";
            type += std::to_string(nLine);
            _obj.changeName(type);
        }
        if(CVector* v = dynamic_cast<CVector*>(&_obj))
        {
            nVector++;
            std::string type = "vector";
            type += std::to_string(nVector);
            _obj.changeName(type);
        }
        if(CPoint* p = dynamic_cast<CPoint*>(&_obj))
        {
            nPoint++;
            std::string type = "point";
            type += std::to_string(nPoint);
            _obj.changeName(type);
        }
    }
    if(alert == on)
    {
        if(space->addObject(_obj))
            std::cout << "Object sucessfully added." << std::endl;
        else
            std::cout << "Couldn't add an object. Name already taken" << std::endl;
    }
    else
        space->addObject(_obj);
}

CSpaceObject *CObjectManager::searchObject(std::string _name)
{return space->getObjectPointer(_name);}

