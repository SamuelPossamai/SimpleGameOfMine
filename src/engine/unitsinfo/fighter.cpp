
#include "animation.h"
#include "unitsinfo/fighter.h"
#include "skills/walk.h"
#include "skills/basicattack.h"

using namespace unitsinfo;

Fighter *Fighter::_info = nullptr;

Fighter::~Fighter() {

    skill::Walk::MemoryInterface::noLongerDepend(10, 140);
    skill::BasicAttack::MemoryInterface::noLongerDepend(50, true);
}

Fighter::Fighter()  {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 140), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::BasicAttack::MemoryInterface::dependentGet(50, true), QPixmap(":/sword_image.png").scaled(50, 50));
}
