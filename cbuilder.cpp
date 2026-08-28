#include "cbuilder.h"
#include "cline.h"
#include "cplane.h"

#include <sstream>

CBuilder::CBuilder(CObjectManager* _m) : manager(_m)
{}

bool CBuilder::buildPlane(std::vector<std::string> &_names)
{
    size_t s = _names.size();
    switch (s)
    {
    case 4: { // trzy punkty i nazwa
        CPoint a[3] = {CPoint()};
        for(size_t i = 0; i < s - 1; ++i) {
            if(resolve<CPoint>(_names[i]))
                a[i] = *resolve<CPoint>(_names[i]);
            else
                return false;
        }
        CPlane newObject(a[0], a[1], a[2]);
        manager->addObject(newObject, &_names[s-1]);
        return true;
    }
    case 3: { // 1 możliwość: dwie linie z nazwą, 2 możliwość: trzy punkty bez nazwy
        if(resolve<CLine>(_names[0])) // możliwość 1
        {
            CLine a[2] = {CLine(CLine::OX) , CLine(CLine::OX)};
            for(size_t i = 0; i < s - 1; ++i) {
                if(resolve<CLine>(_names[i]))
                    a[i] = *resolve<CLine>(_names[i]);
                else
                    return false;
            }
            CPlane newObject(&a[0], &a[1]);
            manager->addObject(newObject, &_names[s-1]);
            return true;
        }
        else // możliwość 2
        {
            CPoint a[3] = {CPoint()};
            for(size_t i = 0; i < s - 1; ++i) {
                if(resolve<CPoint>(_names[i]))
                    a[i] = *resolve<CPoint>(_names[i]);
                else
                    return false;
            }
            CPlane newObject(a[0], a[1], a[2]);
            manager->addObject(newObject, nullptr);
            return true;
        }
    }
    case 2: { // 1 możliwość: wektor z nazwą, 2 możliwość: dwie linie bez nazwy
        if(resolve<CVector>(_names[0])) // możliwość 1
        {
            CVector a = *resolve<CVector>(_names[0]);
            CPlane newObject(a);
            manager->addObject(newObject, &_names[s-1]);
            return true;
        }
        else // możliwość 2
        {
            CLine a[2] = {CLine(CLine::OX) , CLine(CLine::OX)};
            for(size_t i = 0; i < s - 1; ++i) {
                if(resolve<CLine>(_names[i]))
                    a[i] = *resolve<CLine>(_names[i]);
                else
                    return false;
            }
            CPlane newObject(&a[0], &a[1]);
            manager->addObject(newObject, nullptr);
            return true;
        }
    }
    case 1: { // wektor bez nazwy
        if(resolve<CVector>(_names[0])) // możliwość 1
        {
            CVector a = *resolve<CVector>(_names[0]);
            CPlane newObject(a);
            manager->addObject(newObject, nullptr);
            return true;
        }
        else
            return false;
    }
    default:
        return false;
    }

}

bool CBuilder::buildLine(std::vector<std::string> &_names)
{
    size_t s = _names.size();
    switch (s)
    {
    case 3: { // 1 możliwość: dwa punkty i nazwa, 2 możliwość: punkt, wektor i nazwa
        if(resolve<CVector>(_names[0])) // możliwośc 2
        {
            CVector b = *resolve<CVector>(_names[0]);
            CPoint a = CPoint();
            if(resolve<CPoint>(_names[1]))
                a = *resolve<CPoint>(_names[1]);
            else
                return false;
            CLine newObject(a, b);
            manager->addObject(newObject, &_names[s-1]);
            return true;
        }
        else if(resolve<CVector>(_names[1])) // możliwość 2 ale wektor jest w innym miejscu
        {
            CVector b = *resolve<CVector>(_names[1]);
            CPoint a = CPoint();
            if(resolve<CPoint>(_names[0]))
                a = *resolve<CPoint>(_names[0]);
            else
                return false;
            CLine newObject(a, b);
            manager->addObject(newObject, &_names[s-1]);
            return true;
        }
        else // możliwość 1
        {
            CPoint a[2] = {CPoint(), CPoint()};
            for(size_t i = 0; i < s - 1; ++i) {
                if(resolve<CPoint>(_names[i]))
                    a[i] = *resolve<CPoint>(_names[i]);
                else
                    return false;
            }
            CLine newObject(a[0], a[1]);
            manager->addObject(newObject, &_names[s-1]);
            return true;
        }
    }
    case 2: { // 1 możliwość: dwa punkty bez nazwy, 2 możliwość: oś i nazwa
        if(resolve<CPoint>(_names[0])) // możliwość 1
        {
            CPoint a[2] = {CPoint(), CPoint()};
            for(size_t i = 0; i < s - 1; ++i) {
                if(resolve<CPoint>(_names[i]))
                    a[i] = *resolve<CPoint>(_names[i]);
                else
                    return false;
            }
            CLine newObject(a[0], a[1]);
            manager->addObject(newObject, nullptr);
            return true;
        }
        else // możliwość 2
        {
            CLine newObject(CLine::OX);
            if(_names[0] == "OX")
                newObject = CLine(CLine::OX);
            else if(_names[0] == "OY")
                newObject = CLine(CLine::OY);
            else if(_names[0] == "OZ")
                newObject = CLine(CLine::OZ);
            else
                return false;
            manager->addObject(newObject, &_names[s-1]);
            return true;
        }
    }
    case 1: { // oś bez nazwy
        CLine newObject(CLine::OX);
        if(_names[0] == "OX")
            newObject = CLine(CLine::OX);
        else if(_names[0] == "OY")
            newObject = CLine(CLine::OY);
        else if(_names[0] == "OZ")
            newObject = CLine(CLine::OZ);
        else
            return false;
        manager->addObject(newObject, nullptr);
        return true;
    }
    default:
        return false;
    }
}

bool CBuilder::buildVector(std::vector<std::string> &_names)
{
    size_t s = _names.size();
    switch (s)
    {
    case 4: { // trzy liczby i nazwa
        float a[3] = {0};
        for(size_t i = 0; i < s - 1; ++i) {
            std::stringstream ss(_names[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CVector newObject(a[0], a[1], a[2]);
        manager->addObject(newObject, &_names[s-1]);
        return true;
        break;
    }
    case 3: { // 1 możliwość: dwa punkty i nazwa, 2 możliwość: trzy liczby bez nazwy
        if(resolve<CPoint>(_names[0])) // możliwość 1
        {
            CPoint a[2] = {CPoint(), CPoint()};
            for(size_t i = 0; i < s - 1; ++i) {
                if(resolve<CPoint>(_names[i]))
                    a[i] = *resolve<CPoint>(_names[i]);
                else
                    return false;
            }
            CVector newObject(a[0], a[1]);
            manager->addObject(newObject, &_names[s-1]);
            return true;
        }
        else // możliwość 2
        {
            float a[3] = {0};
            for(size_t i = 0; i < s - 1; ++i) {
                std::stringstream ss(_names[i]);
                if(!(ss >> a[i]))
                    return false;
            }
            CVector newObject(a[0], a[1], a[2]);
            manager->addObject(newObject, nullptr);
            return true;
            break;
        }
    }
    case 2: { // dwa punkty bez nazwy
        CPoint a[2] = {CPoint(), CPoint()};
        for(size_t i = 0; i < s - 1; ++i) {
            if(resolve<CPoint>(_names[i]))
                a[i] = *resolve<CPoint>(_names[i]);
            else
                return false;
        }
        CVector newObject(a[0], a[1]);
        manager->addObject(newObject, nullptr);
        return true;
    }
    default:
        return false;
    }
}

bool CBuilder::buildPoint(std::vector<std::string> &_names)
{
    size_t s = _names.size();
    switch (s)
    {
    case 4: { // trzy liczby i nazwa
        float a[3] = {0};
        for(size_t i = 0; i < s - 1; ++i) {
            std::stringstream ss(_names[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CPoint newObject(a[0], a[1], a[2]);
        manager->addObject(newObject, &_names[s-1]);
        return true;
        break;
    }
    case 3: { // trzy liczby
        float a[3] = {0};
        for(size_t i = 0; i < s - 1; ++i) {
            std::stringstream ss(_names[i]);
            if(!(ss >> a[i]))
                return false;
        }
        CPoint newObject(a[0], a[1], a[2]);
        manager->addObject(newObject, nullptr);
        return true;
        break;
    }
    default:
        return false;
        break;
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