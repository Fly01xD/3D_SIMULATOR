#include "cvector.h"
#include <cmath>

CVector::CVector()
    : startPoint(), endPoint()
{
    X = 0; Y = 0; Z = 0;
}

CVector::CVector(CPoint _start, CPoint _end)
    : startPoint(_start), endPoint(_end)
{
    CPoint::X = endPoint.X - startPoint.X;
    CPoint::Y = endPoint.Y - startPoint.Y;
    CPoint::Z = endPoint.Z - startPoint.Z;
}

CVector::CVector(float _x, float _y, float _z)
    : CPoint(_x, _y, _z), startPoint(), endPoint()
{}

float CVector::Determinant(CVector _A, CVector _B, CVector _C)
{
    return (_A.X*_B.Y*_C.Z + _A.Y*_B.Z*_C.X + _A.Z*_B.X*_C.Y
        - _A.Z*_B.Y*_C.X - _A.X*_B.Z*_C.Y - _A.Y*_B.X*_C.Z);
}

CVector* CVector::crossProduct(CVector *_A, CVector *_B)
{
    float x = _A->Y*_B->Z - _A->Z*_B->Y;
    float y = _A->Z*_B->X - _A->X*_B->Z;
    float z = _A->X*_B->Y - _A->Y*_B->X;
    CVector* v = new CVector(x, y, z);
    return v;
}

float CVector::dotProduct(CVector *_A, CVector *_B)
{
    return (_A->X*_B->X + _A->Y*_B->Y + _A->Z*_B->Z);
}

float CVector::modulus()
{
    return sqrt(X*X + Y*Y + Z*Z);
}
