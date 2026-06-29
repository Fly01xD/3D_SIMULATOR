#ifndef CLINE_H
#define CLINE_H

#include "cvector.h"

class CLine
{
public:

    enum axis{
        OX,
        OY,
        OZ
    };

    CLine(axis _ax);
    CLine(CPoint _start, CVector _direction);
private:
    CPoint startPoint;
    CVector directionVector;
};

#endif // CLINE_H
