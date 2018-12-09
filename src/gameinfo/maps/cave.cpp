
#include "maps/cave.h"

using namespace gameinfo::map;

Cave *Cave::_map;

Cave::Cave() : _values(1, 6) {

    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "zu", i+10 }, 50 - 5*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "purple slime", i+12 }, 20 - 2*i);

    _values.add(CreaturesContainerContent{ "white slime", 20 }, 3);
}

Cave::CreaturesContainer Cave::getCreatures() const {

    return _values.getValues();
}
