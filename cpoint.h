#ifndef CPOINT_H
#define CPOINT_H

enum State{
    bad,
    ok
};

class CPoint
{
public:
    CPoint();
    CPoint(float _x, float _y, float _z);
    ~CPoint();

    State mState;
    friend class CVector;
    friend class CLine;
    friend class CPlane;
protected:
    float X;
    float Y;
    float Z;
};

#endif // CPOINT_H
