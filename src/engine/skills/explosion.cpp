
#include <cmath>

#include "utility/random.h"
#include "skills/fireball.h"
#include "skills/explosion.h"
#include "unit.h"

namespace skill {

Explosion *Explosion::_skill = nullptr;

UIntegerType Explosion::action(Unit *u, EngineMap *, ProjectileCreationInterface& pci, const Info& info) {

    if(info.step == 0) if(!u->consumeEnergy(50)) return 0;

    if(info.step < 50) {

        u->setAngle(info.angle);
        return 60;
    }

    if(info.step > 70) return 0;

    for(UIntegerType i = 0; i < 8; i++) {

        Unit::AngleType offset = i*(M_PI/4);

        Fireball::shoot(u, pci, u->angle() + offset);
    }

    return 30;
}

} /* namespace skill */
