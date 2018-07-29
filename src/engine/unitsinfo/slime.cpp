
#include <engine/unit.h>

#include "effects/regeneration.h"
#include "animation.h"
#include "unitsinfo/slime.h"
#include "skills/walk.h"
#include "skills/evade.h"
#include "skills/thrust.h"

namespace unitsinfo {

OneCopyMemoryManager<Slime> Slime::_memmanager;

Slime::Slime(UIntegerType level, const Type& type) : _type(type), _level(level) {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::Evade::getSkill(), QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    addSkill(skill::Thrust::MemoryInterface::dependentGet(12, 90), QPixmap(":/x_simbol.png").scaled(50, 50));

    setSize(22);
    setHealth(100 + 10*level);
    setBaseAttack(5 + level);
    setSpeed(100 + 2*level);

    switch(_type) {

        case Type::Normal:
            break;
        case Type::Fast:
            setHealth(0.8*health());
            setBaseAttack(0.8*baseAttack());
            setSpeed(1.5*speed());
            break;
        case Type::Immortal:
            setHealth(3*health());
            setBaseAttack(0.5*baseAttack());
            setSpeed(0.5*speed());
            break;
        case Type::Crazy:
            setHealth(1.2*health());
            setBaseAttack(1.1*baseAttack());
            setSpeed(1.1*speed());
            break;
        case Type::Ghost:
            setHealth(0.15*health());
            setBaseAttack(0.2*baseAttack());
            setSpeed(5*speed());
    }
}

Slime::~Slime() {

    skill::Walk::MemoryInterface::noLongerDepend(10, 100);
    skill::Thrust::MemoryInterface::noLongerDepend(12, 90);
}

void Slime::init(Unit *u) const {

    if(_type == Type::Immortal) u->addEffect(effect::Regeneration::getEffect(0.1*health(), 100));
}

} /* namespace creature */
