
#ifndef CREATUREMAP_H
#define CREATUREMAP_H

#include <vector>
#include <string>

#include <config/types.h>

/*!
 * \brief Abstract class for creature maps, it's used to return the creatures that appeard when a region is explored
 */
class CreatureMap {

public:

    struct CreaturesContainerContent {

        std::string creature_name;
        UIntegerType creature_level;
    };

    using CreaturesContainer = std::vector<CreaturesContainerContent>;

    /*!
     * \brief Return the creatures that were found exploring the map
     * \return Creatures found in the map
     */
    virtual CreaturesContainer getCreatures() const = 0;
};

#endif // CREATUREMAP_H
