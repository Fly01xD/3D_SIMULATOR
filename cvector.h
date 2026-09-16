#ifndef CVECTOR_H
#define CVECTOR_H

#include "cpoint.h"
class CLine;

// można napisać algorytm dodawania wektorów używając operatorów

class CVector : public CSpaceObject
{
public:
    CVector();
    CVector(CPoint _start, CPoint _end);
    CVector(float _x, float _y, float _z);
    ~CVector();
    std::unique_ptr<CSpaceObject> clone() const override
    { return std::make_unique<CVector>(*this); }

    State mState;
    friend class CLine;
    friend class CReader;
    float Determinant(CVector _A, CVector _B, CVector _C) const;
    CVector crossProduct(CVector* _A, CVector* _B) const;
    float dotProduct(CVector* _A, CVector* _B) const;
    float modulus() const;
private:
    CPoint startPoint;
    CPoint endPoint;
    float X;
    float Y;
    float Z;
};

#endif // CVECTOR_H
