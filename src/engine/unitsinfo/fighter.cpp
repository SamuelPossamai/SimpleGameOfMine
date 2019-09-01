
#include "unitsinfo/fighter.h"

using namespace unitsinfo;

Fighter *Fighter::_info = nullptr;

UnitInfo::Skills Fighter::getSkills(const Unit *) const {

    UnitInfo::Skills s;

    s.push_back({"walk", {{"distance", 140}, {"duration", 10}}});
    s.push_back({"basic attack", {{"distance", 50}}});

    return s;
}
