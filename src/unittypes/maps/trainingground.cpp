
#include <unittypes/maps/trainingground.h>

using namespace map;

TrainingGround *TrainingGround::_map;

TrainingGround::TrainingGround() : _values(1, 3) {

    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "slime", i+1 }, 100 - 30*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "yellow slime", i+1 }, 100 - 32*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "pink slime", i+1 }, 100 - 34*i);
    for(UIntegerType i = 0; i < 3; i++) _values.add(CreaturesContainerContent{ "orange slime", i+1 }, 20 - 5*i);

    _values.add(CreaturesContainerContent{ "purple slime", 1 }, 5);
}

TrainingGround::CreaturesContainer TrainingGround::getCreatures() const {

    return _values.getValues();
}
