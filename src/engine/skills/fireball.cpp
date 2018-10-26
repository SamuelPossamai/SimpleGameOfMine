
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

    p_info.durability = 40 + u->attributes().wisdom();
    p_info.size = 17;
    p_info.speed = 35 + u->attributes().wisdom()/3;
    p_info.damage = 15 + ( 6*u->attributes().wisdom() + u->attributes().dexterity() )/15;

    Unit::AngleType accuracy = M_PI/(2+(4*u->attributes().dexterity() + u->attributes().wisdom())/20);

    Unit::AngleType arrow_angle = angle + utility::Random::realDistribution(-accuracy, accuracy);

    pci.create("fireball", u, p_info, arrow_angle, { u->x() + dx, u->y() + dy }, arrow_angle);
}

} /* namespace skill */
