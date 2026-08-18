#include "cline.h"
#include <cmath>


CLine::CLine(axis _ax)
    : returnedRelation(unknown), mState(ok)
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
{
    if(_direction.modulus() == 0)
        mState = bad;
    else
        mState = ok;
}

CLine::CLine(CPoint _start, CPoint _end)
    : returnedRelation(unknown)
{
    directionVector = CVector(_start, _end);
    startPoint = _start;
    if(directionVector.modulus() == 0)
        mState = bad;
    else
        mState = ok;
}

CLine::~CLine()
{}


// obliczanie punktu przecięcia prostych
CLine CLine::calculatePoint(CLine* _line)
{

    float v1[3] = {directionVector.X, directionVector.Y, directionVector.Z};
    float p1[3] = {startPoint.X, startPoint.Y, startPoint.Z};

    // SPRAWDZENIE JAKIE SĄ WZGLĘDEM SIEBIE PROSTE

    CVector checkVector = directionVector.crossProduct(&directionVector, &_line->directionVector);
    float epsilon = 1e-6;
    bool areParallel = (std::abs(checkVector.X) < epsilon &&
        std::abs(checkVector.Y) < epsilon && std::abs(checkVector.Z) < epsilon);

    if(!areParallel) // jeśli proste nie są równoległe
    {
        CVector p1p2(startPoint, _line->startPoint);
        float W = p1p2.Determinant(directionVector, _line->directionVector, p1p2);
        if(std::abs(W) > epsilon)  // jeśli proste są skośne
        {
             _line->setRelation(skew);
            returnedRelation = skew;
            CLine returnedLine(startPoint, calcEndPoint(_line));
            returnedLine.setRelation(skew);
            return returnedLine;
        }
        else // jeśli nie są skośne
        {     // jeśli stosunek wektorów nie jest liczbą rzeczywistą (skalar)
            float t, point[3];
            bool exist = true;
            CVector p1p2(startPoint, _line->startPoint);
            CVector p1p2_x_v2 = p1p2.crossProduct(&p1p2, &_line->directionVector);
            CVector v1_x_v2 = directionVector.crossProduct(&directionVector, &_line->directionVector);

            // poniżej obliczenie punktu
            t = p1p2.dotProduct(&p1p2_x_v2, &v1_x_v2)/(v1_x_v2.modulus() * v1_x_v2.modulus());
            for(int i =0; i < 3; i++) // przypisanie punktu
                point[i] = p1[i] + v1[i]*t;

            if(exist) // ostateczne zwrócenie punktu
            {
                _line->setRelation(intersecting);
                returnedRelation = intersecting;
                // mState tego obiektu będzie 'bad' (zerowy kierunek — to punkt, nie linia),
                // ale to nieistotne: liczy się tylko returnedRelation, ustawiane niżej.
                CLine returnedLine(CPoint(point[0],point[1],point[2]), CVector());
                returnedLine.setRelation(intersecting);
                return returnedLine;
            }
            else
                return CLine(CPoint(),CVector());
        }
    }
    else //jeśli proste są równoległe
    {
        CVector p1p2(startPoint, _line->startPoint);
        CVector checkVector = p1p2.crossProduct(&p1p2, &directionVector);
        bool areIdentical = (std::abs(checkVector.X) < epsilon
            && std::abs(checkVector.Y) < epsilon && std::abs(checkVector.Z) < epsilon);

        if(areIdentical)
        {
            _line->setRelation(identical);
            returnedRelation = identical;
            CLine returnedLine = *_line;
            return returnedLine;
        }
        else
        {
            _line->setRelation(parallel);
            returnedRelation = parallel;

            CLine returnedLine(startPoint, calcEndPoint(_line));
            returnedLine.setRelation(parallel);
            return returnedLine;
        }
    }
}

CPoint CLine::calcEndPoint(CLine* _line) // metoda prywatna do liczenia punktu nabliżeszego między prostymi
{
    float epsilon = 1e-6;
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
    float t;
    if(std::abs(rate) > epsilon)
    {
        t = -constant / rate;
    }
    else
    {
        // v1 i v2 są prostopadłe: żaden punkt na _line nie spełni ściśle
        // (point - p1)·v1 = 0, chyba że constant == 0 (wtedy każdy pasuje).
        // Zamiast tego bierzemy rzut ortogonalny p1 na _line — czyli
        // najbliższy punkt na _line względem p1. Mianownik v2·v2 > 0
        // zawsze, bo _line ma niezerowy wektor kierunkowy.
        float v2v2 = a2*a2 + b2*b2 + c2*c2;
        t = ((x1-x2)*a2 + (y1-y2)*b2 + (z1-z2)*c2) / v2v2;
    }

    CPoint point(x2+a2*t, y2+b2*t, z2+c2*t);
    return point;
}
