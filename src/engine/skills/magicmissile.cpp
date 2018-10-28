
#include <cmath>

#include "utility/random.h"
#include "projectilefactories/missilefactory.h"
#include "skills/magicmissile.h"
#include "unit.h"
#include "enginemap.h"

using namespace skill;

MagicMissile *MagicMissile::_skill = nullptr;

UIntegerType MagicMissile::action(Unit *u, EngineMap *, ProjectileCreationInterface& pci, const Info& info) {

    if(info.step == 0) if(!u->consumeEnergy(20)) return 0;

    if(info.step < 30) {

        u->setAngle(info.angle);
        return 35;
    }

    if(info.step > 60) return 0;

    Unit::AngleType missile_angle_precision = 5*M_PI/(0.2*u->accuracy() + u->magicControl());
    Unit::AngleType missile_start_angle = u->angle() +
            utility::Random::realDistribution(-missile_angle_precision, missile_angle_precision);

    Unit::PositionType dx = 50*std::cos(missile_start_angle);
    Unit::PositionType dy = 50*std::sin(missile_start_angle);

    projectilefactory::MissileFactory::MissileInfo p_info;

    p_info.durability = 0.3*u->magicPower();
    p_info.size = 20;
    p_info.speed = 30 + u->magicPower()/4;
    p_info.damage = u->magicPower()/2;
    p_info.angular_speed = 0.05 + 0.0015*u->magicControl();

    Unit::AngleType accuracy = 20*M_PI/(u->accuracy() + u->magicControl());

    Unit::AngleType missile_angle = missile_start_angle + utility::Random::realDistribution(-accuracy, accuracy);

    pci.create("magic missile", u, p_info, missile_angle, { u->x() + dx, u->y() + dy }, missile_angle);

    return 30;
}
