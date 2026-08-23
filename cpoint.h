#ifndef CPOINT_H
#define CPOINT_H

#include "cspaceobject.h"

enum State{
    bad,
    ok
};

class CPoint : public CSpaceObject
{
public:
    CPoint();
    CPoint(float _x, float _y, float _z);
    ~CPoint();

    State mState;
    friend class CVector;
    friend class CLine;
    friend class CPlane;
private:
    float X;
    float Y;
    float Z;
};

#endif // CPOINT_H
