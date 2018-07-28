
#include <cmath>

#include "skills/walk.h"
#include "unit.h"
#include "map.h"

namespace skill {

Walk::MemoryManager Walk::_skills(_clone);

UIntegerType Walk::action(Unit *u, Map *m, const Info& info) {

    if(info.step == 0) u->setAngle(info.angle);

    return doAction(u, m, info, u->angle());
}

UIntegerType Walk::doAction(Unit *u, Map *, const Info& info, RealType angle){

    static const UIntegerType period = 3;

    if(info.step >= period*_dur) return 0;

    Unit::PositionType dx = _ds*cos(angle);
    Unit::PositionType dy = _ds*sin(angle);

    u->setPos(u->x() + dx, u->y() + dy);

    return period;
}

} /* namespace skill */
