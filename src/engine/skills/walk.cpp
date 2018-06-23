
#include <cmath>

#include "skills/walk.h"
#include "unit.h"
#include "map.h"

namespace skill {

UIntegerType Walk::action(Unit *u, Map *m, const Info& info) {

    return doAction(u, m, info, info.angle);
}

UIntegerType Walk::doAction(Unit *u, Map *, const Info& info, RealType angle){

    if(info.step == 0) u->setAngle(angle);

    if(info.step >= 3*_dur) return 0;

    UIntegerType dx = _ds*cos(angle);
    UIntegerType dy = _ds*sin(angle);

    u->setPos(u->x() + dx, u->y() + dy);

    return 3;
}

} /* namespace skill */
