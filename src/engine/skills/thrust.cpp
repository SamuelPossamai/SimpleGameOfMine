
#include <cmath>

#include "skills/thrust.h"
#include "unit.h"
#include "enginemap.h"

namespace skill {

OneCopyMemoryManager<Thrust> Thrust::_skills;

UIntegerType Thrust::action(Unit *u, EngineMap *m, ProjectileCreationInterface&, const Info& info) {

    EngineMap::UnitsVector v;

    EngineMap::PointType::CoordType x = RealType(u->x()) + 0.9*u->size()*cos(u->angle());
    EngineMap::PointType::CoordType y = RealType(u->y()) + 0.9*u->size()*sin(u->angle());

    m->unitsInRange(v, { x, y }, 0.1*u->size());

    if(v.size() > 1) for(Unit *unit : v) if(unit->team() != u->team()) u->attack(unit, u->baseDamage());

    return Walk::doAction(u, m, info, u->angle());
}

UnitSkill *Thrust::create(const sutils::VariantDataInfo& m) {

    UIntegerType distance = 100;
    UIntegerType duration = 10;

    auto it = m.find("distance");

    if(it != m.end()) {

        if(it->second.isNumber()) distance = decltype(distance)(it->second.getNumber());
        else std::cerr << "skill::Thrust: Distance passed is not a number" << std::endl;
    }

    it = m.find("duration");

    if(it != m.end()) {

        if(it->second.isNumber()) duration = decltype(duration)(it->second.getNumber());
        else std::cerr << "skill::Thrust: Duration passed is not a number" << std::endl;
    }

    return MemoryInterface::dependentGet(duration, distance);
}

void Thrust::destroy() {

    MemoryInterface::noLongerDepend(*this);
}

} /* namespace skill */
