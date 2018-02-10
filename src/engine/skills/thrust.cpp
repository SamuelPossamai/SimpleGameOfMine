
#include <cmath>

#include "skills/thrust.h"
#include "unit.h"
#include "map.h"

#include <iostream>

namespace skill {

UIntegerType Thrust::action(Unit *u, Map *m, const Info& info) {

    Map::UnitsVector v;

    Map::PointType::CoordType x = RealType(u->x()) + u->size()*cos(u->angle());
    Map::PointType::CoordType y = RealType(u->y()) + u->size()*sin(u->angle());

    m->unitsInRange(v, { x, y }, 0);

    if(v.size() > 1) {

        for(Unit *unit : v) {

            if(unit->team() != u->team()) {

                auto new_health_value = unit->health() - 1;

                if(new_health_value > unit->health()) new_health_value = unit->health();

                unit->setHealth(new_health_value);
                std::cout << "attack: " << u->team() << std::endl;
            }
        }
    }

    return Walk::doAction(u, m, info, u->angle());
}

} /* namespace skill */
