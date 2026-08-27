#ifndef CCONSOLE_H
#define CCONSOLE_H
#include <optional>

#include "cobjectmanager.h"

class C3D;

enum objectType{
    plane,
    line,
    vector,
    point
};

class CConsole
{
    C3D* app;
    alertStatus input;
    alertStatus output;
public:
    CConsole(C3D* _a);
    ~CConsole();
    void getInstruction();
    void failToCreate();
    void create(objectType _type,
        std::optional<std::string> _name1 = std::nullopt,
        std::optional<std::string> _name2 = std::nullopt,
        std::optional<std::string> _name3 = std::nullopt,
        std::optional<std::string> _name4 = std::nullopt);
};

#endif // CCONSOLE_H
