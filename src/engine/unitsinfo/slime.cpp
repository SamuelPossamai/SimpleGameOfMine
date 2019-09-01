
#include <engine/unit.h>

#include "effects/regeneration.h"
#include "unitsinfo/slime.h"

using namespace unitsinfo;

OneCopyMemoryManager<Slime> Slime::_memmanager;

UnitInfo::Skills Slime::getSkills(const Unit *) const {

    UnitInfo::Skills s;

    s.push_back({"walk", {{"distance", 100}, {"duration", 10}}});
    s.push_back({"evade", {}});
    s.push_back({"thrust", {{"distance", 90}, {"duration", 12}}});

    return s;
}

void Slime::init(Unit *u) const {

    if(_type == Type::Immortal) u->addEffect(effect::Regeneration::getEffect(0.1*u->maxHealth(), 100));
}

Slime::HealthType Slime::healthCalculate(const Attributes& attr, UIntegerType level) const {

    HealthType value = HealthType(100 + 10*attr.vitality() + 0.5*attr.strength() + level);

    switch(_type) {

    case Type::Normal:
        break;
    case Type::Fast:
        value *= 0.8;
        break;
    case Type::Immortal:
        value *= 3;
        break;
    case Type::Crazy:
        value *= 1.2;
        break;
    case Type::Ghost:
        value *= 0.15;
        break;
    }

    return value;
}

Slime::AttackType Slime::attackCalculate(const Attributes& attr, UIntegerType) const  {

    AttackType value = AttackType(5 + 0.9*attr.strength() + 0.2*attr.dexterity());

    switch(_type) {

    case Type::Normal:
        break;
    case Type::Fast:
        value *= 0.8;
        break;
    case Type::Immortal:
        value *= 0.5;
        break;
    case Type::Crazy:
        value *= 1.1;
        break;
    case Type::Ghost:
        value *= 0.2;
        break;
    }

    return value;
}

Slime::SpeedType Slime::speedCalculate(const Attributes& attr, UIntegerType) const {

    SpeedType value = SpeedType(100 + 1.6*attr.agility() + 0.4*attr.dexterity());

    switch(_type) {

    case Type::Normal:
        break;
    case Type::Fast:
        value *= 1.5;
        break;
    case Type::Immortal:
        value *= 0.5;
        break;
    case Type::Crazy:
        value *= 1.1;
        break;
    case Type::Ghost:
        value *= 5;
        break;
    }

    return value;
}
