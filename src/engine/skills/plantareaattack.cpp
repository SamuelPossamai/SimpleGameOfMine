
#include <cmath>

#include <engine/unit.h>
#include <engine/enginemap.h>

#include "skills/plantareaattack.h"

using namespace skill;

PlantAreaAttack *PlantAreaAttack::_skill = nullptr;

UIntegerType PlantAreaAttack::action(Unit *u, EngineMap *m, ProjectileCreationInterface&, const Info& i) {

    if(i.step > 50) return 0;

    if(i.step/10 & 1) u->setAngle(u->angle() + M_PI/6);
    else u->setAngle(u->angle() - M_PI/6);

    auto v = m->unitsInRange(u->pos(), 100);

    for(Unit *other_unit : v) if(other_unit->team() != u->team()) u->attack(other_unit, u->unitInfo()->baseAttack()/2);

    return 5;
}
