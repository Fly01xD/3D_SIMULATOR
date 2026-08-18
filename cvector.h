#ifndef CVECTOR_H
#define CVECTOR_H

#include "cpoint.h"
class CLine;

// można napisać algorytm dodawania wektorów używając operatorów

class CVector : protected CPoint
{
public:
    CVector();
    CVector(CPoint _start, CPoint _end);
    CVector(float _x, float _y, float _z);
    ~CVector();

    State mState;
    friend class CLine;
    float Determinant(CVector _A, CVector _B, CVector _C);
    CVector crossProduct(CVector* _A, CVector* _B);
    float dotProduct(CVector* _A, CVector* _B);
    float modulus();
private:
    CPoint startPoint;
    CPoint endPoint;
};

#endif // CVECTOR_H
