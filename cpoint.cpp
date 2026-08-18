#include "cpoint.h"

CPoint::CPoint()
    : X(0), Y(0), Z(0), mState(ok)
{}

CPoint::CPoint(float _x, float _y, float _z)
    : X(_x), Y(_y), Z(_z), mState(ok)
{}

CPoint::~CPoint()
{}
