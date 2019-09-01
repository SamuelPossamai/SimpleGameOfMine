
#include <cmath>

#include "unitsinfo/knight.h"

using namespace unitsinfo;

Knight *Knight::_info = nullptr;

UnitInfo::Skills Knight::getSkills(const Unit *) const {

    UnitInfo::Skills s;

    s.push_back({"walk", {{"distance", 100}, {"duration", 10}}});
    s.push_back({"basic attack", {{"distance", 80}}});
    s.push_back({"rage", {}});

    return s;
}

Knight::SpeedType Knight::speedCalculate(const Attributes& attr, UIntegerType) const {

    return SpeedType(45 + 0.7*std::sqrt(attr.agility()*attr.strength()) + 0.1*(attr.dexterity() + attr.agility()));
}
