#ifndef CCONSOLE_H
#define CCONSOLE_H
#include <optional>
#include <vector>

#include "cobjectmanager.h"
#include "objectType.h"

class C3D;
struct SInode;

class CConsole
{
    C3D* app;
    consoleStatus input;
    consoleStatus output;
public:
    CConsole(C3D* _a);
    ~CConsole();
    void Instruction();

    void changeInput(consoleStatus _i) {input = _i;}
    void changeOutput(consoleStatus _o) {output = _o;}

    void failToCreate();
    void failToRemove(std::string _name);
    void removedSuccesfully(std::string _name);
    void failToFind();
    void write(std::string _text);
    void writeInode(SInode _info);

    void remove(std::vector<std::string>& _names);
    void removeAt(size_t _i);
    void clearSpace();
    void create(objectType _type,
        std::optional<std::string> _arg1 = std::nullopt,
        std::optional<std::string> _arg2 = std::nullopt,
        std::optional<std::string> _arg3 = std::nullopt,
        std::optional<std::string> _arg4 = std::nullopt);
    void list(objectType _type);
    std::optional<std::string> getNameAt(size_t _i);
    void chooseAt(size_t _i);
    void choose(std::string _name);
    SInode chosenMod();
    SInode chosenInfo();
    SInode chosenCrossProduct(std::string _name);
    SInode chosenDotProduct(std::string _name);
    void unchoose();
    void save();
    void save(std::string _name);
};

#endif // CCONSOLE_H
