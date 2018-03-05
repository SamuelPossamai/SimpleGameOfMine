
#include "skills/evade.h"
#include "unit.h"
#include "map.h"

namespace skill {

UIntegerType Evade::action(Unit *u, Map *m, const Info& info) {

    if(info.step < 10) {

        UIntegerType dx = 10*cos(u->angle());
        UIntegerType dy = 10*sin(u->angle());

        u->setAngle(u->angle() + 0.05);

        m->setUnitPosition(u, Map::PointType(u->x() - dx, u->y() - dy));

        return 2;
    }

    return 0;
}

} /* namespace skill */
