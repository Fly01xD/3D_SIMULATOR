#ifndef CCONSOLE_H
#define CCONSOLE_H
#include <optional>
#include <vector>

#include "cobjectmanager.h"

class C3D;

enum objectType{
    all,
    plane,
    line,
    vector,
    point
};

class CConsole
{
    C3D* app;
    consoleStatus input;
    consoleStatus output;
public:
    CConsole(C3D* _a);
    ~CConsole();
    void getInstruction();

    void changeInput(consoleStatus _i) {input = _i;}
    void changeOutput(consoleStatus _o) {output = _o;}

    void failToCreate();
    void failToRemove(std::string _name);
    void removed(std::string _name);
    void failToFind(std::string _name);
    void write(std::string _text);

    void remove(std::vector<std::string>& _names);
    void create(objectType _type,
        std::optional<std::string> _name1 = std::nullopt,
        std::optional<std::string> _name2 = std::nullopt,
        std::optional<std::string> _name3 = std::nullopt,
        std::optional<std::string> _name4 = std::nullopt);
    void list(objectType _type);
};

#endif // CCONSOLE_H
