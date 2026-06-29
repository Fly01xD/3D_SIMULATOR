#ifndef CVECTOR_H
#define CVECTOR_H

#include "cpoint.h"

class CVector : protected CPoint
{
public:
    CVector();
    CVector(CPoint _start, CPoint _end);
private:
    CPoint startPoint;
    CPoint endPoint;
};

#endif // CVECTOR_H
