
#include <cmath>

#include "skills/thrust.h"
#include "unit.h"
#include "map.h"

namespace skill {

UIntegerType Thrust::action(Unit *u, Map *m, const Info& info) {

    Map::UnitsVector v;

    Map::PointType::CoordType x = RealType(u->x()) + 0.9*u->size()*cos(u->angle());
    Map::PointType::CoordType y = RealType(u->y()) + 0.9*u->size()*sin(u->angle());

    m->unitsInRange(v, { x, y }, 0.1*u->size());

    if(v.size() > 1) for(Unit *unit : v) if(unit->team() != u->team()) unit->receiveDamage(1);

    return Walk::doAction(u, m, info, u->angle());
}

} /* namespace skill */