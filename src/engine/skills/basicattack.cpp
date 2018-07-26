
#include <cmath>

#include "map.h"
#include "unit.h"
#include "skills/basicattack.h"

using namespace skill;

OneCopyMemoryManager<BasicAttack> BasicAttack::_skills;

UIntegerType BasicAttack::action(Unit *u, Map *m, const Info& info) {

    u->setAngle(info.angle);

    Map::AngleType angle = u->angle();

    if(info.step < 10) return 10;
    else if(info.step < 20) angle -= (20*M_PI)/180;
    else if(info.step < 30) angle -= (10*M_PI)/180;
    else if(info.step < 40) angle -= (0*M_PI)/180;
    else return 0;

    Map::UnitsVector v;

    Map::PositionType x = u->x() + _distance*std::cos(angle);
    Map::PositionType y = u->y() + _distance*std::sin(angle);

    m->unitsInRange(v, { x, y }, 0);

    for(Unit *unit : v) if(unit->team() != u->team()) u->attack(unit, u->unitInfo()->baseAttack());

    return 5;
}
