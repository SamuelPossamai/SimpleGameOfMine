
#include "skills/evade.h"
#include "unit.h"

namespace skill {

UIntegerType Evade::action(Unit *u, Map*, const Info& info) {

    if(info.step < 10) {

        UIntegerType dx = 10*cos(u->angle());
        UIntegerType dy = 10*sin(u->angle());

        u->setAngle(u->angle() + 0.05);

        u->setX(u->x() - dx);
        u->setY(u->y() - dy);

        return 2;
    }

    return 0;
}

} /* namespace skill */
