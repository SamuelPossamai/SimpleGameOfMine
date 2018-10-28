
#include "utility/random.h"

#include "unitattributes.h"

using namespace utility;

UnitAttributes UnitAttributes::generateRandom(UIntegerType level) {

    UnitAttributes attr;
    UIntegerType points = level*freePointsPerLevel();
    for(UIntegerType i = 0; i < points; i++) {

        attr.assignPoint(Random::uniformIntDistribution(0, 32213) % statsCount());
    }

    return attr;
}
