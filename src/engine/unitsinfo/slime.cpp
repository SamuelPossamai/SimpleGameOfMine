
#include <engine/unit.h>

#include "effects/regeneration.h"
#include "animation.h"
#include "unitsinfo/slime.h"
#include "skills/walk.h"
#include "skills/evade.h"
#include "skills/thrust.h"

using namespace unitsinfo;

OneCopyMemoryManager<Slime> Slime::_memmanager;

Slime::Slime(const Type& type) : _type(type) {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::Evade::getSkill(), QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    addSkill(skill::Thrust::MemoryInterface::dependentGet(12, 90), QPixmap(":/x_simbol.png").scaled(50, 50));
}

Slime::~Slime() {

    skill::Walk::MemoryInterface::noLongerDepend(10, 100);
    skill::Thrust::MemoryInterface::noLongerDepend(12, 90);
}

void Slime::init(Unit *u) const {

    if(_type == Type::Immortal) u->addEffect(effect::Regeneration::getEffect(0.1*u->maxHealth(), 100));
}

Slime::HealthType Slime::healthCalculate(const Attributes& attr, UIntegerType level) const {

    UIntegerType value = 100 + 10*attr.vitality() + 0.5*attr.strength() + level;

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

    UIntegerType value = 5 + 0.9*attr.strength() + 0.2*attr.dexterity();

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

    UIntegerType value = 100 + 1.6*attr.agility() + 0.4*attr.dexterity();

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
