
#include "unitsinfo/ninja.h"

using namespace unitsinfo;

Ninja *Ninja::_info = nullptr;

UnitInfo::Skills Ninja::getSkills(const Unit *u) const {

    UnitInfo::Skills s = Fighter::getSkills(u);

    s.push_back({"teleport", {}});
    s.push_back({"ON/OFF last escape", {}});
    s.push_back({"throw shuriken", {}});

    return s;
}
