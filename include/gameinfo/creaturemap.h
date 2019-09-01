
#ifndef GAMEINFO_CREATUREMAP_H
#define GAMEINFO_CREATUREMAP_H

#include <vector>
#include <string>

#include <config/types.h>

#include "unitattributes.h"

namespace gameinfo {

/*!
 * \brief Abstract class for creature maps, it's used to return the creatures that appeard when a region is explored
 */
class CreatureMap {

public:

    struct CreaturesContainerContent {

        std::string creature_type;
        UIntegerType creature_level;
    };

    using CreaturesContainer = std::vector<CreaturesContainerContent>;

    CreatureMap() = default;
    virtual ~CreatureMap() = default;

    /*!
     * \brief Return the creatures that were found exploring the map
     * \return Creatures found in the map
     */
    virtual CreaturesContainer getCreatures() const = 0;
};

} /* namespace gameinfo */

#endif // GAMEINFO_CREATUREMAP_H
