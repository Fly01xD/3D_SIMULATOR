#include "cplane.h"
#include "cline.h"

CPlane::CPlane(CVector _normal)
{
    normalVector = _normal;
    if(_normal.modulus() == 0)
        mState = bad;
    else
        mState = ok;
}

CPlane::CPlane(CLine* _line1, CLine* _line2)
{
    CLine connection = _line1->calculatePoint(_line2);
    if(connection.getRelation() == CLine::parallel)
    {
        // obliczanie weketora normalnego:
        CVector v = connection.directionVector.crossProduct(
            &connection.directionVector,&_line1->directionVector);

        normalVector = v;
        if(normalVector.modulus() == 0)
            mState = bad;
        else
            mState = ok;
    }
    else if(connection.getRelation() == CLine::intersecting)
    {
        CVector v = connection.directionVector.crossProduct(
            &_line1->directionVector, &_line2->directionVector);

        normalVector = v;
        if(normalVector.modulus() == 0)
            mState = bad;
        else
            mState = ok;
    }
    else
    {
        normalVector = CVector();
        mState = bad;
    }
}

CPlane::CPlane(CPoint _point1, CPoint _point2, CPoint _point3)
{
    CLine line1(_point1,_point2);
    CLine line2(_point2,_point3);
    if(line1.mState == bad || line2.mState == bad) // sprawdzenie czy dwa lub więcej punktów nie są identyczne
    {
        normalVector = CVector();
        mState = bad;
    }
    else
    {
        CLine line3 = line1.calculatePoint(&line2);
        if(line3.returnedRelation == CLine::identical)
        {
            normalVector = CVector();
            mState = bad;
        }
        else // jeśli prosta nie spełnia powyższych to musi być "intersecting"
        {
            normalVector = line1.directionVector.crossProduct(
                &line1.directionVector, &line2.directionVector);
            mState = ok;
        }
    }
}

CPlane::~CPlane()
{}