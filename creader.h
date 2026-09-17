#ifndef CREADER_H
#define CREADER_H

#include "SInode.h"
class CSpaceObject;

class CReader
{
private:
    CSpaceObject* toRead = nullptr;
    SInode inode;
    CSpaceObject* stash = nullptr;

    void clearInode();
public:
    CReader();
    CReader(CSpaceObject* _obj);
    ~CReader();

    const SInode getInode() {return inode;}
    void changeObject(CSpaceObject* _obj) {toRead = _obj;}
    CSpaceObject* getStash() {return stash;}
    bool readObject();
    bool readObject(CSpaceObject* _obj);
    bool readModulus();
    bool readCrossProduct(CSpaceObject* _obj);
    bool readDotProduct(CSpaceObject* _obj);
    bool readyToRead();
    void clear();
    void clearStash();
};

#endif // CREADER_H
