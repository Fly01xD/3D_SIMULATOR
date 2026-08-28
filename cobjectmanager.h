#ifndef COBJECTMANAGER_H
#define COBJECTMANAGER_H

#include <string>
class CSpace;
class CSpaceObject;

enum consoleStatus{
    on,
    off
};

class CObjectManager
{
private:
    CSpace* space;
    consoleStatus alert;
    unsigned nPlane;
    unsigned nLine;
    unsigned nVector;
    unsigned nPoint;
public:
    CObjectManager(CSpace* _s);
    ~CObjectManager();
    void alertON() {alert = on;}
    void alertOFF() {alert = off;}
    void toggleAlert() {if(alert == on) alert = off;
        else alert = on;}
    bool addObject(CSpaceObject &_obj, const std::string *_name);
    CSpaceObject* searchObject(std::string _name);
    CSpaceObject* objectAt(const size_t _i);
    const size_t spaceSize();
    bool removeObject(const CSpaceObject &_obj);
};

#endif // COBJECTMANAGER_H
