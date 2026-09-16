#include "c3d.h"

int main() {

    C3D Sim;
    CConsole* console = Sim.setupConsole(off, on);
    console->create(point, "0", "0", "0");
    console->create(point, "1", "1", "0");
    console->create(point, "0", "0", "1");
    console->create(line, "point1", "point2");
    console->create(line, "point1", "point3");
    console->list(all);
    std::vector<std::string> bin;
    for(unsigned i = 1; i<4; i++)
    {
        std::optional<std::string> name = console->getNameAt(i);
        if(name)
            bin.push_back(*name);
    }
    console->remove(bin);
    console->list(all);
    console->chooseAt(1);
    console->chosenMod();
    console->chosenCrossProduct("line2");
    console->save("product");
    console->list(all);
    console->unchoose();
    return 0;
}
