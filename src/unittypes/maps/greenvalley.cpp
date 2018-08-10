
#include <unittypes/maps/greenvalley.h>

using namespace map;

GreenValley *GreenValley::_map;

GreenValley::GreenValley() : _values(1, 6) {

    for(UIntegerType i = 0; i < 6; i++) _values.add(CreaturesContainerContent{ "slime", i+1 }, 100 - 10*i);
    for(UIntegerType i = 0; i < 4; i++) _values.add(CreaturesContainerContent{ "yellow slime", i+3 }, 80 - 10*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "pink slime", i+4 }, 70 - 12*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "blue slime", i+5 }, 50 - 5*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "purple slime", i+8 }, 12 - 2*i);
    for(UIntegerType i = 0; i < 2; i++) _values.add(CreaturesContainerContent{ "orange slime", i+3 }, 7 - i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "white slime", i+6 }, 3);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "monster plant", i+10 }, 5);
}

GreenValley::CreaturesContainer GreenValley::getCreatures() const {

    return _values.getValues();
}
