#ifndef CLINE_H
#define CLINE_H

#include "cvector.h"

class CLine : public CSpaceObject
{
public:
    enum axis{ OX, OY, OZ};
    enum relation{ parallel, skew, identical, intersecting, unknown};
    friend class CPlane;
    friend class CReader;

    CLine(axis _ax);
    CLine(CPoint _start, CVector _direction);
    CLine(CPoint _start, CPoint _end);
    ~CLine();
    std::unique_ptr<CSpaceObject> clone() const override
    { return std::make_unique<CLine>(*this); }

    State mState;
    CLine calculatePoint(CLine* _line);
    void setRelation(relation _r) {returnedRelation = _r;}
    relation getRelation() const {return returnedRelation;}
private:
    relation returnedRelation;
    CPoint startPoint;
    CVector directionVector;

    CPoint calcEndPoint(CLine *_line);
};

#endif // CLINE_H
