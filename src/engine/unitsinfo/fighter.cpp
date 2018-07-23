
#include "animation.h"
#include "unitsinfo/fighter.h"
#include "skills/walk.h"
#include "skills/basicattack.h"

namespace unitsinfo {

Fighter::MemoryManager Fighter::_copies;

Fighter::~Fighter() {

    skill::Walk::MemoryInterface::noLongerDepend(10, 140);
    skill::BasicAttack::MemoryInterface::noLongerDepend(15);
}

Fighter::Fighter(const Attributes& attr) : UnitClassInfo(attr, 20) {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 140), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::BasicAttack::MemoryInterface::dependentGet(50), QPixmap(":/x_simbol.png").scaled(50, 50));

    calculateInfo();
}

} /* namespace creature */
