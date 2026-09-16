#ifndef SINODE_H
#define SINODE_H

#include "objectType.h"
#include <vector>

struct SInode{
    objectType type;
    std::vector<float> values;
    // jeśli jest prosta, to najpierw w values jest vector, potem point
};

#endif // SINODE_H
