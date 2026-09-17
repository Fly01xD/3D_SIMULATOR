#include "cbuilder.h"
#include "cline.h"
#include "cplane.h"

#include <sstream>
#include <optional>

CBuilder::CBuilder(CObjectManager* _m) : manager(_m)
{}

CBuilder::~CBuilder()
{}

bool CBuilder::buildPlane(std::vector<std::string> &_arguments)
{
    size_t s = _arguments.size();
    switch (s)
    {
    case 4: { // trzy punkty i nazwa
        CPoint a[3] = {CPoint()};
        for(size_t i = 0; i < s - 1; ++i) {
            if(CPoint* ptr = resolve<CPoint>(_arguments[i]))
                a[i] = *ptr;
            else
                return false;
        }
        CPlane newObject(a[0], a[1], a[2]);
        return manager->addObject(newObject, _arguments[s-1]);
    }
    case 3: { // 1 możliwość: dwie linie z nazwą, 2 możliwość: trzy punkty bez nazwy
        if(resolve<CLine>(_arguments[0])) // możliwość 1
        {
            CLine a[2] = {CLine(CLine::OX) , CLine(CLine::OX)};
            for(size_t i = 0; i < s - 1; ++i) {
                if(CLine* ptr = resolve<CLine>(_arguments[i]))
                    a[i] = *ptr;
                else
                    return false;
            }
            CPlane newObject(&a[0], &a[1]);
            return manager->addObject(newObject, _arguments[s-1]);
        }
        else // możliwość 2
        {
            CPoint a[3] = {CPoint()};
            for(size_t i = 0; i < s; ++i) {
                if(CPoint* ptr = resolve<CPoint>(_arguments[i]))
                    a[i] = *ptr;
                else
                    return false;
            }
            CPlane newObject(a[0], a[1], a[2]);
            return manager->addObject(newObject, std::nullopt);
        }
    }
    case 2: { // 1 możliwość: wektor z nazwą, 2 możliwość: dwie linie bez nazwy
        if(resolve<CVector>(_arguments[0])) // możliwość 1
        {
            CVector a = *resolve<CVector>(_arguments[0]);
            CPlane newObject(a);
            return manager->addObject(newObject, _arguments[s-1]);
        }
        else // możliwość 2
        {
            CLine a[2] = {CLine(CLine::OX) , CLine(CLine::OX)};
            for(size_t i = 0; i < s; ++i) {
                if(CLine* ptr = resolve<CLine>(_arguments[i]))
                    a[i] = *ptr;
                else
                    return false;
            }
            CPlane newObject(&a[0], &a[1]);
            return manager->addObject(newObject, std::nullopt);
        }
    }
    case 1: { // wektor bez nazwy
        if(resolve<CVector>(_arguments[0])) // możliwość 1
        {
            CVector a = *resolve<CVector>(_arguments[0]);
            CPlane newObject(a);
            return manager->addObject(newObject, std::nullopt);
        }
        else
            return false;
    }
    default:
        return false;
    }

}

bool CBuilder::buildLine(std::vector<std::string> &_arguments)
{
    size_t s = _arguments.size();
    switch (s)
    {
    case 3: { // 1 możliwość: dwa punkty i nazwa, 2 możliwość: punkt, wektor i nazwa
        if(resolve<CVector>(_arguments[0])) // możliwośc 2
        {
            CVector b = *resolve<CVector>(_arguments[0]);
            CPoint a = CPoint();
            if(CPoint* ptr = resolve<CPoint>(_arguments[1]))
                a = *ptr;
            else
                return false;
            CLine newObject(a, b);
            return manager->addObject(newObject, _arguments[s-1]);
        }
        else if(resolve<CVector>(_arguments[1])) // możliwość 2 ale wektor jest w innym miejscu
        {
            CVector b = *resolve<CVector>(_arguments[1]);
            CPoint a = CPoint();
            if(CPoint* ptr = resolve<CPoint>(_arguments[0]))
                a = *ptr;
            else
                return false;
            CLine newObject(a, b);
            return manager->addObject(newObject, _arguments[s-1]);
        }
        else // możliwość 1
        {
            CPoint a[2] = {CPoint(), CPoint()};
            for(size_t i = 0; i < s - 1; ++i) {
                if(CPoint* ptr = resolve<CPoint>(_arguments[i]))
                    a[i] = *ptr;
                else
                    return false;
            }
            CLine newObject(a[0], a[1]);
            return manager->addObject(newObject, _arguments[s-1]);
        }
    }
    case 2: { // 1 możliwość: dwa punkty bez nazwy, 2 możliwość: oś i nazwa
        if(resolve<CPoint>(_arguments[0])) // możliwość 1
        {
            CPoint a[2] = {CPoint(), CPoint()};
            for(size_t i = 0; i < s; ++i) {
                if(CPoint* ptr = resolve<CPoint>(_arguments[i]))
                    a[i] = *ptr;
                else
                    return false;
            }
            CLine newObject(a[0], a[1]);
            return manager->addObject(newObject, std::nullopt);
        }
        else // możliwość 2
        {
            CLine newObject(CLine::OX);
            if(_arguments[0] == "OX")
                newObject = CLine(CLine::OX);
            else if(_arguments[0] == "OY")
                newObject = CLine(CLine::OY);
            else if(_arguments[0] == "OZ")
                newObject = CLine(CLine::OZ);
            else
                return false;
            return manager->addObject(newObject, _arguments[s-1]);
        }
    }
    case 1: { // oś bez nazwy
        CLine newObject(CLine::OX);
        if(_arguments[0] == "OX")
            newObject = CLine(CLine::OX);
        else if(_arguments[0] == "OY")
            newObject = CLine(CLine::OY);
        else if(_arguments[0] == "OZ")
            newObject = CLine(CLine::OZ);
        else
            return false;
        return manager->addObject(newObject, nullptr);
    }
    default:
        return false;
    }
}

bool CBuilder::buildVector(std::vector<std::string> &_arguments)
{
    size_t s = _arguments.size();
    switch (s)
    {
    case 4: { // trzy liczby i nazwa
        float a[3] = {0};
        for(size_t i = 0; i < s - 1; ++i) {
            std::stringstream ss(_arguments[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CVector newObject(a[0], a[1], a[2]);
        return manager->addObject(newObject, _arguments[s-1]);
    }
    case 3: { // 1 możliwość: dwa punkty i nazwa, 2 możliwość: trzy liczby bez nazwy
        if(resolve<CPoint>(_arguments[0])) // możliwość 1
        {
            CPoint a[2] = {CPoint(), CPoint()};
            for(size_t i = 0; i < s - 1; ++i) {
                if(CPoint* ptr = resolve<CPoint>(_arguments[i]))
                    a[i] = *ptr;
                else
                    return false;
            }
            CVector newObject(a[0], a[1]);
            return manager->addObject(newObject, _arguments[s-1]);
        }
        else // możliwość 2
        {
            float a[3] = {0};
            for(size_t i = 0; i < s; ++i) {
                std::stringstream ss(_arguments[i]);
                if(!(ss >> a[i]))
                    return false;
            }
            CVector newObject(a[0], a[1], a[2]);
            return manager->addObject(newObject, nullptr);
        }
    }
    case 2: { // dwa punkty bez nazwy
        CPoint a[2] = {CPoint(), CPoint()};
        for(size_t i = 0; i < s; ++i) {
            if(CPoint* ptr = resolve<CPoint>(_arguments[i]))
                a[i] = *ptr;
            else
                return false;
        }
        CVector newObject(a[0], a[1]);
        return manager->addObject(newObject, nullptr);
    }
    default:
        return false;
    }
}

bool CBuilder::buildPoint(std::vector<std::string> &_arguments)
{
    size_t s = _arguments.size();
    switch (s)
    {
    case 4: { // trzy liczby i nazwa
        float a[3] = {0};
        for(size_t i = 0; i < s - 1; ++i) {
            std::stringstream ss(_arguments[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CPoint newObject(a[0], a[1], a[2]);
        return manager->addObject(newObject, _arguments[s-1]);
    }
    case 3: { // trzy liczby
        float a[3] = {0};
        for(size_t i = 0; i < s; ++i) {
            std::stringstream ss(_arguments[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CPoint newObject(a[0], a[1], a[2]);
        return manager->addObject(newObject, std::nullopt);
    }
    default:
        return false;
    }
}

template<typename T>
T *CBuilder::resolve(const std::string &_name)
{
    CSpaceObject* obj = manager->searchObject(_name);
    if(!obj)
        return nullptr;
    return dynamic_cast<T*>(obj);
}