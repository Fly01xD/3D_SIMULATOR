#ifndef CPLANE_H
#define CPLANE_H
#include "cvector.h"

class CPlane : public CSpaceObject
{
public:
    CPlane(CVector _normal);
    CPlane(CLine* _line1, CLine* _line2);
    CPlane(CPoint _point1, CPoint _point2, CPoint _point3);
    ~CPlane();
    friend class CReader;
    std::unique_ptr<CSpaceObject> clone() const override
    { return std::make_unique<CPlane>(*this); }

    State mState;
private:
    CVector normalVector;
};

#endif // CPLANE_H
