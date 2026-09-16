#include "creader.h"
#include "cline.h"
#include "cplane.h"

CReader::CReader() : toRead(nullptr)
{
    inode.type = unknown;
    inode.values.clear();
}

CReader::CReader(CSpaceObject *_obj) : toRead(_obj)
{
    readObject();
}

CReader::~CReader()
{}

bool CReader::readObject()
{
    inode.type = unknown;
    inode.values.clear();

    if(!toRead)
        return false;
    else
    {
        if(CPlane* p = dynamic_cast<CPlane*>(toRead))
        {
            inode.type = plane;
            inode.values.push_back(p->normalVector.X);
            inode.values.push_back(p->normalVector.Y);
            inode.values.push_back(p->normalVector.Z);
            return true;
        }
        else if(CLine* l = dynamic_cast<CLine*>(toRead))
        {
            inode.type = line;
            inode.values.push_back(l->directionVector.X);
            inode.values.push_back(l->directionVector.Y);
            inode.values.push_back(l->directionVector.Z);
            inode.values.push_back(l->startPoint.X);
            inode.values.push_back(l->startPoint.Y);
            inode.values.push_back(l->startPoint.Z);
            return true;
        }
        else if(CVector* v = dynamic_cast<CVector*>(toRead))
        {
            inode.type = vector;
            inode.values.push_back(v->X);
            inode.values.push_back(v->Y);
            inode.values.push_back(v->Z);
            return true;
        }
        else if(CPoint* p = dynamic_cast<CPoint*>(toRead))
        {
            inode.type = point;
            inode.values.push_back(p->X);
            inode.values.push_back(p->Y);
            inode.values.push_back(p->Z);
            return true;
        }
        else
            return false;
    }
}

bool CReader::readObject(CSpaceObject *_obj)
{
    inode.type = unknown;
    inode.values.clear();

    if(!_obj)
        return false;
    else
    {
        if(CPlane* p = dynamic_cast<CPlane*>(_obj))
        {
            inode.type = plane;
            inode.values.push_back(p->normalVector.X);
            inode.values.push_back(p->normalVector.Y);
            inode.values.push_back(p->normalVector.Z);
            return true;
        }
        else if(CLine* l = dynamic_cast<CLine*>(_obj))
        {
            inode.type = line;
            inode.values.push_back(l->directionVector.X);
            inode.values.push_back(l->directionVector.Y);
            inode.values.push_back(l->directionVector.Z);
            inode.values.push_back(l->startPoint.X);
            inode.values.push_back(l->startPoint.Y);
            inode.values.push_back(l->startPoint.Z);
            return true;
        }
        else if(CVector* v = dynamic_cast<CVector*>(_obj))
        {
            inode.type = vector;
            inode.values.push_back(v->X);
            inode.values.push_back(v->Y);
            inode.values.push_back(v->Z);
            return true;
        }
        else if(CPoint* p = dynamic_cast<CPoint*>(_obj))
        {
            inode.type = point;
            inode.values.push_back(p->X);
            inode.values.push_back(p->Y);
            inode.values.push_back(p->Z);
            return true;
        }
        else
            return false;
    }
}

bool CReader::readModulus()
{
    inode.type = unknown;
    inode.values.clear();

    if(CPoint* p = dynamic_cast<CPoint*>(toRead))
    {
        inode.type = point;
        return false;
    }
    else
    {
        if(CPlane* p = dynamic_cast<CPlane*>(toRead))
        {
            inode.type = plane;
            inode.values.push_back(p->normalVector.modulus());
            return true;
        }
        else if(CLine* l = dynamic_cast<CLine*>(toRead))
        {
            inode.type = line;
            inode.values.push_back(l->directionVector.modulus());
            return true;
        }
        else if(CVector* v = dynamic_cast<CVector*>(toRead))
        {
            inode.type = vector;
            inode.values.push_back(v->modulus());
            return true;
        }
        else
            return false;
    }
}

bool CReader::calculateCrossProduct(CSpaceObject *_obj)
{
    if(!toRead || !_obj)
        return false;
    CReader tmpReader(_obj);
    readObject();
    if(inode.type == unknown || inode.type == all || inode.type == point)
        return false;
    if(tmpReader.inode.type == unknown || tmpReader.inode.type == all || tmpReader.inode.type == point)
        return false;
    if(tmpReader.inode.type == inode.type)
    {
        if(inode.type == plane)
        {
            CPlane* plane1 = dynamic_cast<CPlane*>(toRead);
            CPlane* plane2 = dynamic_cast<CPlane*>(_obj);
            static CVector v = plane1->normalVector.crossProduct(&plane1->normalVector, &plane2->normalVector);
            readObject(&v);
            stash = &v;
            return true;
        }
        else if(inode.type == line)
        {
            CLine* line1 = dynamic_cast<CLine*>(toRead);
            CLine* line2 = dynamic_cast<CLine*>(_obj);
            static CVector v = line1->directionVector.crossProduct(&line1->directionVector, &line2->directionVector);
            readObject(&v);
            stash = &v;
            return true;
        }
        else if(inode.type == vector)
        {
            CVector* vector1 = dynamic_cast<CVector*>(toRead);
            CVector* vector2 = dynamic_cast<CVector*>(_obj);
            static CVector v = vector1->crossProduct(vector1, vector2);
            readObject(&v);
            stash = &v;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool CReader::readyToRead()
{
    if(toRead == nullptr)
        return false;
    else
        return true;
}

void CReader::clear()
{
    toRead = nullptr;
    stash = nullptr;
}

void CReader::clearStash()
{
    stash = nullptr;
}
