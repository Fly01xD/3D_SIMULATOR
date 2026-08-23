#include "cvector.h"
#include <cmath>

CVector::CVector()
    : startPoint(), endPoint(), mState(ok)
{
    X = 0; Y = 0; Z = 0;
}

CVector::CVector(CPoint _start, CPoint _end)
    : startPoint(_start), endPoint(_end), mState(ok)
{
    X = endPoint.X - startPoint.X;
    Y = endPoint.Y - startPoint.Y;
    Z = endPoint.Z - startPoint.Z;
}

CVector::CVector(float _x, float _y, float _z)
    : X(_x), Y(_y), Z(_z), startPoint(), endPoint(_x, _y, _z), mState(ok)
{}

CVector::~CVector()
{}

float CVector::Determinant(CVector _A, CVector _B, CVector _C) const
{
    return (_A.X*_B.Y*_C.Z + _A.Y*_B.Z*_C.X + _A.Z*_B.X*_C.Y
        - _A.Z*_B.Y*_C.X - _A.X*_B.Z*_C.Y - _A.Y*_B.X*_C.Z);
}

CVector CVector::crossProduct(CVector *_A, CVector *_B) const
{
    float x = _A->Y*_B->Z - _A->Z*_B->Y;
    float y = _A->Z*_B->X - _A->X*_B->Z;
    float z = _A->X*_B->Y - _A->Y*_B->X;
    CVector v(x, y, z);
    return v;
}

float CVector::dotProduct(CVector *_A, CVector *_B) const
{
    return (_A->X*_B->X + _A->Y*_B->Y + _A->Z*_B->Z);
}

float CVector::modulus() const
{
    return sqrt(X*X + Y*Y + Z*Z);
}
