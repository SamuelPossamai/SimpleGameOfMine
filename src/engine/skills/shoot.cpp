
#include <iostream>
#include <cmath>

#include "utility/random.h"
#include "skills/shoot.h"
#include "unit.h"
#include "enginemap.h"

namespace skill {

UIntegerType Shoot::action(Unit *u, EngineMap *, ProjectileCreationInterface& pci, const Info& info) {

    Unit::AngleType accuracy = 15*M_PI/u->accuracy();

    if(info.step < 25) {

        u->setAngle(info.angle);
        return 30;
    }

    if(info.step > 45) return 0;

    Unit::PositionType dx = 40*std::cos(u->angle());
    Unit::PositionType dy = 40*std::sin(u->angle());

    gameinfo::Projectiles::ProjectileInfo p_info;

    p_info.durability = 13;
    p_info.size = 15;
    p_info.speed = 30 + u->baseDamage()/3 + u->baseSpeed()/5;
    p_info.damage = u->baseDamage()/3 + u->accuracy()/10;

    Unit::AngleType arrow_angle = u->angle() + utility::Random::realDistribution(-accuracy, accuracy);

    pci.create(_projectile_type, u, p_info, arrow_angle, { u->x() + dx, u->y() + dy }, arrow_angle);

    return 20;
}

UnitSkill *Shoot::create(const utility::VariantDataInfo& d) {

    auto it = d.find("projectile");

    if(it == d.end()) {

        std::cerr << "skill::Shoot: Projectile not passed" << std::endl;

        return nullptr;
    }

    return new Shoot(it->second.get<utility::Variant::String>());
}

} /* namespace skill */
