
#include <cmath>

#include "utility/random.h"
#include "skills/fireball.h"
#include "unit.h"
#include "enginemap.h"

namespace skill {

Fireball *Fireball::_skill = nullptr;

UIntegerType Fireball::action(Unit *u, EngineMap *, ProjectileCreationInterface& pci, const Info& info) {

    if(info.step == 0) if(!u->consumeEnergy(3)) return 0;

    if(info.step < 25) {

        u->setAngle(info.angle);
        return 30;
    }

    if(info.step > 45) return 0;

    shoot(u, pci, u->angle());

    return 25;
}

void Fireball::shoot(Unit *u, ProjectileCreationInterface& pci, Unit::AngleType angle) {

    Unit::PositionType dx = 55*std::cos(angle);
    Unit::PositionType dy = 55*std::sin(angle);

    gameinfo::Projectiles::ProjectileInfo p_info;

    p_info.durability = u->magicPower();
    p_info.size = 17;
    p_info.speed = 35 + u->magicPower()/3;
    p_info.damage = u->magicPower();

    Unit::AngleType accuracy = 15*M_PI/(u->accuracy() + 0.8*u->magicControl());

    Unit::AngleType arrow_angle = angle + utility::Random::realDistribution(-accuracy, accuracy);

    pci.create("fireball", u, p_info, arrow_angle, { u->x() + dx, u->y() + dy }, arrow_angle);
}

} /* namespace skill */
