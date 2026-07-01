#ifndef CPOINT_H
#define CPOINT_H

class CPoint
{
public:
    CPoint();
    CPoint(float _x, float _y, float _z);
    ~CPoint();

    friend class CVector;
    friend class CLine;
protected:
    float X;
    float Y;
    float Z;
};

#endif // CPOINT_H
