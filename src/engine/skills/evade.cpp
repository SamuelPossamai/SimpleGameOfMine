
#include "skills/evade.h"
#include "unit.h"
#include "map.h"

namespace skill {

Evade *Evade::_skill = nullptr;

UIntegerType Evade::action(Unit *u, Map *, const Info& info) {

    if(info.step < 10) {

        Unit::PositionType dx = 10*cos(u->angle());
        Unit::PositionType dy = 10*sin(u->angle());

        u->setAngle(u->angle() + 0.05);

        u->setPos(u->x() - dx, u->y() - dy);;

        return 2;
    }

    return 0;
}

} /* namespace skill */
