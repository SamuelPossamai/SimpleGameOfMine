
#include <cmath>

#include "utility/random.h"
#include "unitsinfo/unitclassinfo.h"
#include "skills/shoot.h"
#include "unit.h"
#include "enginemap.h"

namespace skill {

Shoot *Shoot::_skill = nullptr;

UIntegerType Shoot::action(Unit *u, EngineMap *, ProjectileCreationInterface& pci, const Info& info) {

    const unitsinfo::UnitClassInfo *u_info = static_cast<const unitsinfo::UnitClassInfo *>(u->unitInfo());

    Unit::AngleType accuracy = M_PI/(2+u_info->attributes().dexterity()/5);

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
    p_info.speed = 40 + u_info->attributes().strength()/3 + u_info->speed()/5;
    p_info.damage = 10 + ( 3*u_info->attributes().strength() + 2*u_info->attributes().dexterity() )/15;

    Unit::AngleType arrow_angle = u->angle() + utility::Random::realDistribution(-accuracy, accuracy);

    pci.create("arrow", u, p_info, arrow_angle, { u->x() + dx, u->y() + dy }, arrow_angle);

    return 20;
}

} /* namespace skill */
