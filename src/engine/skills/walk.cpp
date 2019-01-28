
#include <cmath>

#include "skills/walk.h"
#include "unit.h"
#include "enginemap.h"

namespace skill {

Walk::MemoryManager Walk::_skills(_clone);

UIntegerType Walk::action(Unit *u, EngineMap *m, ProjectileCreationInterface&, const Info& info) {

    if(info.step == 0) u->setAngle(info.angle);

    return doAction(u, m, info, u->angle());
}

UIntegerType Walk::doAction(Unit *u, EngineMap *, const Info& info, RealType angle){

    static const UIntegerType period = 3;

    if(info.step >= period*_dur) return 0;

    Unit::PositionType dx = _ds*cos(angle);
    Unit::PositionType dy = _ds*sin(angle);

    u->setPos(u->x() + dx, u->y() + dy);

    return period;
}

UnitSkill *Walk::create(const utility::VariantDataInfo& m) {

    auto distance = decltype(_ds)(100);
    auto duration = decltype(_dur)(10);

    auto it = m.find("distance");

    if(it != m.end()) {

        if(it->second.isNumber()) distance = decltype(distance)(it->second.getNumber());
        else std::cerr << "skill::Walk: Distance passed is not a number" << std::endl;
    }

    it = m.find("duration");

    if(it != m.end()) {

        if(it->second.isNumber()) duration = decltype(duration)(it->second.getNumber());
        else std::cerr << "skill::Walk: Duration passed is not a number" << std::endl;
    }

    return MemoryInterface::dependentGet(duration, distance);
}

void Walk::destroy() {

    MemoryInterface::noLongerDepend(*this);
}

} /* namespace skill */
