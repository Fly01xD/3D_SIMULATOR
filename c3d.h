#ifndef C3D_H
#define C3D_H

#include "cbuilder.h"
#include "cconsole.h"
#include "cobjectmanager.h"
#include "cspace.h"
#include "creader.h"

class C3D
{
private:
    CSpace space;
    CObjectManager manager;
    CConsole console;
    CBuilder builder;
    CReader reader;
public:
    C3D();
    ~C3D();
    CConsole* setupConsole(consoleStatus _input, consoleStatus _output);
    void create(objectType _type, std::vector<std::string>& _names);
    void remove(std::vector<std::string>& _names);
    void removeAt(size_t _i);
    void clearSpace();
    std::optional<std::string> getNameAt(size_t _i);
    std::vector<SInode> list(objectType _type);
    void choose(std::string name);
    void chooseAt(size_t _i);
    SInode chosenMod();
    SInode chosenInfo();
    SInode chosenCrossProduct(std::string _name);
    void clearChosen();
    void saveStash(std::optional<std::string> _name);

};

#endif // C3D_H
