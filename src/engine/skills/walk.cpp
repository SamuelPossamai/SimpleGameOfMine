
#include <cmath>

#include "skills/walk.h"
#include "unit.h"

namespace skill {

UIntegerType Walk::action(Unit *u, Map*, const Info& info) {

    if(info.step == 0) u->setAngle(info.angle);

    if(info.step >= 3*_dur) return 0;

    UIntegerType dx = _ds*cos(info.angle);
    UIntegerType dy = _ds*sin(info.angle);

    u->setX(u->x() + dx);
    u->setY(u->y() + dy);

    return info.step + 3;
}

} /* namespace skill */
