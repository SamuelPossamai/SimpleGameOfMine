
#include "skills/walk.h"
#include "unitsinfo/zu.h"

using namespace unitsinfo;

Zu *Zu::_info = nullptr;

Zu::Zu() {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
}

Zu::~Zu(){

    skill::Walk::MemoryInterface::noLongerDepend(10, 100);
}
