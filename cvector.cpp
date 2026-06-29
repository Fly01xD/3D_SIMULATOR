#include "cvector.h"

CVector::CVector()
    : startPoint(), endPoint()
{
    X = 0; Y = 0; Z = 0;
}

CVector::CVector(CPoint _start, CPoint _end)
    : startPoint(_start), endPoint(_end)
{
    X = endPoint.X - startPoint.X;
    Y = endPoint.Y - startPoint.Y;
    Z = endPoint.Z - startPoint.Z;
}
