#ifndef COBJECTMANAGER_H
#define COBJECTMANAGER_H

#include <string>
class CSpace;
class CSpaceObject;

enum alertStatus{
    on,
    off
};

class CObjectManager
{
private:
    CSpace* space;
    alertStatus alert;
    int nPlane;
    int nLine;
    int nVector;
    int nPoint;
public:
    CObjectManager();
    void alertON() {alert = on;}
    void alertOFF() {alert = off;}
    void toggleAlert() {if(alert == on) alert = off;
        else alert = on;}
    void addObject(CSpaceObject &_obj, const std::string *_name);
};

#endif // COBJECTMANAGER_H
