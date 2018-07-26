
#ifndef CREATUREMAP_H
#define CREATUREMAP_H

#include <vector>
#include <string>

#include <config/types.h>

class CreatureMap {

public:

    struct CreaturesContainerContent {

        std::string creature_name;
        UIntegerType creature_level;
    };

    using CreaturesContainer = std::vector<CreaturesContainerContent>;

    virtual CreaturesContainer getCreatures() const = 0;
};

#endif // CREATUREMAP_H
