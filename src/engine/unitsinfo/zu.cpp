
#include "skills/walk.h"
#include "unitsinfo/zu.h"

using namespace unitsinfo;

Zu *Zu::_info = nullptr;

UnitInfo::Skills Zu::getSkills(const Unit *) const {

    UnitInfo::Skills s;

    s.push_back({"walk", {{"distance", 100}, {"duration", 10}}});

    return s;
}
