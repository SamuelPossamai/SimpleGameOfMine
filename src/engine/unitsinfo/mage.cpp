
#include "unit.h"
#include "unitsinfo/mage.h"

using namespace unitsinfo;

UnitInfo::Skills Mage::getSkills(const Unit *) const {

    UnitInfo::Skills s;

    s.push_back({"walk", {{"distance", 100}, {"duration", 10}}});
    s.push_back({"magic missile", {}});
    s.push_back({"teleport", {}});
    s.push_back({"fireball", {}});
    s.push_back({"explosion", {}});
    s.push_back({"ON/OFF magic shield", {}});

    return s;
}
