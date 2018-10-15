
#include <cmath>

#include "enginemap.h"
#include "unit.h"
#include "skills/basicattack.h"

using namespace skill;

OneCopyMemoryManager<BasicAttack> BasicAttack::_skills;

UIntegerType BasicAttack::action(Unit *u, EngineMap *m, ProjectileCreationInterface&, const Info& info) {

    u->setAngle(info.angle);

    EngineMap::AngleType angle = u->angle();

    EngineMap::AngleType angle_dif = 0;
    if(info.step < 10) return 10;
    if(info.step < 20) angle_dif = (20*M_PI)/180;
    else if(info.step < 30) angle_dif = (10*M_PI)/180;
    else if(info.step < 40) angle_dif = (0*M_PI)/180;
    else return 0;

    if(_att_from_above) angle_dif = -angle_dif;

    angle += angle_dif;

    EngineMap::UnitsVector v;

    EngineMap::PositionType x = u->x() + _distance*std::cos(angle);
    EngineMap::PositionType y = u->y() + _distance*std::sin(angle);

    m->unitsInRange(v, { x, y }, _distance/5);

    for(Unit *unit : v) if(unit->team() != u->team()) u->attack(unit, u->unitInfo()->baseAttack());

    return 5;
}
