
#include <unittypes/maps/greenvalley.h>

using namespace map;

GreenValley *GreenValley::_map;

GreenValley::GreenValley() : _values(1, 6) {

    for(UIntegerType i = 0; i < 6; i++) _values.add(CreaturesContainerContent{ "slime", i+1 }, 100 - 10*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "blue slime", i+5 }, 50 - 5*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "purple slime", i+8 }, 10 - 2*i);
}

GreenValley::CreaturesContainer GreenValley::getCreatures() const {

    return _values.getValues();
}
