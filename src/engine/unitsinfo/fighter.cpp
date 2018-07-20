
#include "animation.h"
#include "unitsinfo/fighter.h"
#include "skills/walk.h"

namespace unitsinfo {

Fighter::MemoryManager Fighter::_copies;

Fighter::~Fighter() {

    skill::Walk::MemoryInterface::noLongerDepend(10, 140);
    skill::Walk::MemoryInterface::noLongerDepend(60, 0);
}

Fighter::Fighter(const Attributes& attr) : UnitClassInfo(attr, 20) {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 140), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::Walk::MemoryInterface::dependentGet(60, 0), QPixmap(":/x_simbol.png").scaled(50, 50));

    setSize(20);
    setHealth(20);
    setSpeed(100);
}

} /* namespace creature */
