
#include <cmath>

#include "utility/random.h"
#include "unitsinfo/unitclassinfo.h"
#include "projectilefactories/missilefactory.h"
#include "skills/magicmissile.h"
#include "unit.h"
#include "enginemap.h"

using namespace skill;

MagicMissile *MagicMissile::_skill = nullptr;

UIntegerType MagicMissile::action(Unit *u, EngineMap *, ProjectileCreationInterface& pci, const Info& info) {

    const unitsinfo::UnitClassInfo *u_info = static_cast<const unitsinfo::UnitClassInfo *>(u->unitInfo());

    if(info.step == 0) if(!u->consumeEnergy(20)) return 0;

    if(info.step < 30) {

        u->setAngle(info.angle);
        return 35;
    }

    if(info.step > 60) return 0;

    Unit::AngleType missile_angle_precision = 2*M_PI/(1+(u_info->attributes().dexterity() + 3*u_info->attributes().wisdom())/10);
    Unit::AngleType missile_start_angle = u->angle() +
            utility::Random::realDistribution(-missile_angle_precision, missile_angle_precision);

    Unit::PositionType dx = 50*std::cos(missile_start_angle);
    Unit::PositionType dy = 50*std::sin(missile_start_angle);

    projectilefactory::MissileFactory::MissileInfo p_info;

    p_info.durability = 10 + u_info->attributes().wisdom()/10;
    p_info.size = 20;
    p_info.speed = 30 + u_info->attributes().wisdom()/4;
    p_info.damage = 13 + ( 5*u_info->attributes().wisdom() + u_info->attributes().dexterity() )/15;
    p_info.angular_speed = 0.05 + 0.002*u_info->attributes().wisdom();

    Unit::AngleType accuracy = 2*M_PI/(1+(u_info->attributes().dexterity() + u_info->attributes().wisdom())/5);

    Unit::AngleType missile_angle = missile_start_angle + utility::Random::realDistribution(-accuracy, accuracy);

    pci.create("magic missile", u, p_info, missile_angle, { u->x() + dx, u->y() + dy }, missile_angle);

    return 30;
}
