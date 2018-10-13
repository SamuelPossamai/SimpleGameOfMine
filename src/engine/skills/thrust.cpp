
#include <cmath>

#include "skills/thrust.h"
#include "unit.h"
#include "map.h"

namespace skill {

OneCopyMemoryManager<Thrust> Thrust::_skills;

UIntegerType Thrust::action(Unit *u, EngineMap *m, ProjectileCreationInterface&, const Info& info) {

    EngineMap::UnitsVector v;

    EngineMap::PointType::CoordType x = RealType(u->x()) + 0.9*u->size()*cos(u->angle());
    EngineMap::PointType::CoordType y = RealType(u->y()) + 0.9*u->size()*sin(u->angle());

    m->unitsInRange(v, { x, y }, 0.1*u->size());

    if(v.size() > 1) for(Unit *unit : v) if(unit->team() != u->team()) u->attack(unit, u->unitInfo()->baseAttack());

    return Walk::doAction(u, m, info, u->angle());
}

} /* namespace skill */
