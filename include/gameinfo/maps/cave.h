
#ifndef MAP_CAVE_H
#define MAP_CAVE_H

#include "utility/randomvalues.h"
#include "creaturemap.h"

namespace gameinfo {

namespace map {

class Cave : public CreatureMap {

    Cave();

public:

    virtual CreaturesContainer getCreatures() const override;

    static Cave *getMap() { if(!_map) _map = new Cave; return _map; }

private:

    utility::RandomValues<CreaturesContainerContent> _values;

    static Cave *_map;
};

} /* namespace map */

} /* namespace gameinfo */

#endif // MAP_CAVE_H
