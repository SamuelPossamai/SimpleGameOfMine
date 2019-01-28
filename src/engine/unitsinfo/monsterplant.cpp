
#include "unitsinfo/monsterplant.h"

using namespace unitsinfo;

MonsterPlant *MonsterPlant::_info = nullptr;

UnitInfo::Skills MonsterPlant::getSkills(const Unit *) const {

    UnitInfo::Skills s;

    s.push_back({"walk", {{"distance", 80}, {"duration", 15}}});
    s.push_back({"plant area attack", {}});

    return s;
}
