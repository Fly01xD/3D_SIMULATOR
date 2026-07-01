#include "cline.h"
#include <cmath>


CLine::CLine(axis _ax)
    : returnedRelation(unknown)
{
    startPoint = CPoint(0, 0, 0);
    if(_ax == axis::OX)
        directionVector = CVector(startPoint, CPoint(1, 0, 0));
    else if(_ax == axis::OY)
        directionVector = CVector(startPoint, CPoint(0, 1, 0));
    else
        directionVector = CVector(startPoint, CPoint(0, 0, 1));
}

CLine::CLine(CPoint _start, CVector _direction)
    : startPoint(_start), directionVector(_direction), returnedRelation(unknown)
{}

CLine::CLine(CPoint _start, CPoint _end)
    : returnedRelation(unknown)
{
    directionVector = CVector(_start, _end);
    startPoint = _start;
}


// obliczanie punktu przecięcia prostych
CLine *CLine::calculatePoint(CLine* _line)
{

    float v1[3] = {directionVector.X, directionVector.Y, directionVector.Z};
    float v2[3] = {_line->directionVector.X, _line->directionVector.Y, _line->directionVector.Z};
    float p1[3] = {startPoint.X, startPoint.Y, startPoint.Z};
    float p2[3] = {_line->startPoint.X, _line->startPoint.Y, _line->startPoint.Z};

    // SPRAWDZENIE JAKIE SĄ WZGLĘDEM SIEBIE PROSTE

    int checker = 0;    // odliczanie równych stosunków wektorów
    for(int i = 0; i < 3; i++)
    {
        float k, s;
        if(i < 2)
        {
            k = v1[i]/v2[i];
            s = v1[i+1]/v2[i+1];
        }
        else
        {
            k = v1[i]/v2[i];
            s = v1[i-2]/v2[i-2];
        }
        if(k == s)
            checker++;
    }
    if(checker < 3) // sprawdzenie czy proste nie są równoległe
    {
        CVector p1p2(startPoint, _line->startPoint);
        float W = p1p2.Determinant(directionVector, _line->directionVector, p1p2);
        if(W != 0)  // sprawdzenie czy przypadkiem proste nie sa skośne
        {
            _line->setRelation(skew);
            returnedRelation = skew;
            CLine* returnedLine = new CLine(startPoint, calcEndPoint(_line)); // jescze do dokończenia
            returnedLine->setRelation(skew);
            return returnedLine;
        }
        else // jeśli nie są
        {     // jeśli stosunek wektorów nie jest liczbą rzeczywistą (skalar)
            float t, point[3];
            bool exist = true;
            for(int i = 0; i < 3; i++)
            {
                if(v2[i] - v1[i] != 0)
                {
                    t = (p1[i] - p2[i])/(v2[i] - v1[i]);
                    point[i] = p1[i] + v1[i]*t;
                }
                else
                {
                    if(p1[i] == p2[i])
                        point[i] = p1[i];
                    else
                        exist = false;
                }
            }
            if(exist)
            {
                _line->setRelation(intersecting);
                returnedRelation = intersecting;
                CLine* returnedLine = new CLine(CPoint(point[0],point[1],point[2]), CVector());
                returnedLine->setRelation(intersecting);
                return returnedLine;
            }
            else
                return nullptr;
        }
    }
    else //jeśli proste są równoległe
    {
        float parameters[3];
        for(int i = 0; i< 3; i++)
        {
            parameters[i] = (p1[i] - p2[i])/v2[i];
        }
        if(parameters[0] == parameters[1] == parameters[2])
        {
            _line->setRelation(identical);
            returnedRelation = identical;
            return _line;
        }
        else
        {
            _line->setRelation(parallel);
            returnedRelation = parallel;

            CLine* returnedLine = new CLine(startPoint, calcEndPoint(_line)); // jescze do dokończenia
            returnedLine->setRelation(parallel);
            return returnedLine;
        }
    }
}

CPoint CLine::calcEndPoint(CLine* _line) // metoda prywatna do liczenia punktu nabliżeszego między prostymi
{
    float x2 = _line->startPoint.X;
    float x1 = startPoint.X;
    float a2 = _line->directionVector.X;
    float a1 = directionVector.X;

    float y2 = _line->startPoint.Y;
    float y1 = startPoint.Y;
    float b2 = _line->directionVector.Y;
    float b1 = directionVector.Y;

    float z2 = _line->startPoint.Z;
    float z1 = startPoint.Z;
    float c2 = _line->directionVector.Z;
    float c1 = directionVector.Z;

    float constant = (x2-x1)*a1 + (y2-y1)*b1 + (z2-z1)*c1;
    float rate = a2*a1 + b2*b1 + c2*c1;
    float t = -constant/rate;

    CPoint point(x2+a2*t, y2+b2*t, z2+c2*t);
    return point;
}
