
#include "animation.h"
#include "unitsinfo/fighter.h"
#include "skills/walk.h"
#include "skills/basicattack.h"

#include "gameinfo/skills.h"
#include "unitskillfactory.h"

using namespace unitsinfo;

Fighter *Fighter::_info = nullptr;

Fighter::~Fighter() {

    skill::Walk::MemoryInterface::noLongerDepend(10, 140);
    //skill::BasicAttack::MemoryInterface::noLongerDepend(50, true);
}

Fighter::Fighter()  {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 140), QPixmap(":/wing_boot.png").scaled(50, 50));

    auto i = *gameinfo::Skills::get("basic attack");

    addSkill(i.factory->create(), i.icon);
}
