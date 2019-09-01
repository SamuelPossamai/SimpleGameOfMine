
#include "unitsinfo/archer.h"

using namespace unitsinfo;

UnitInfo::Skills Archer::getSkills(const Unit *u) const {

    UnitInfo::Skills s = Fighter::getSkills(u);

    s.push_back({"shoot arrow", {}});

    return s;
}
