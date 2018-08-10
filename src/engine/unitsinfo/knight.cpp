
#include <cmath>

#include "animation.h"
#include "unitsinfo/knight.h"
#include "skills/walk.h"
#include "skills/basicattack.h"
#include "skills/rage.h"

using namespace unitsinfo;

Knight::MemoryManager Knight::_copies;

Knight::~Knight() {

    skill::Walk::MemoryInterface::noLongerDepend(10, 100);
    skill::BasicAttack::MemoryInterface::noLongerDepend(90, false);
}

Knight::Knight(const Attributes& attr) : UnitClassInfo(attr) {

    addSkill(skill::Walk::MemoryInterface::dependentGet(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::BasicAttack::MemoryInterface::dependentGet(80, false), QPixmap(":/sword_image.png").scaled(50, 50));
    addSkill(skill::Rage::getSkill(), QPixmap(":/rage_img.png"));

    calculateInfo();
}

Knight::SpeedType Knight::speedCalculate() const {

    return 45 + 0.7*std::sqrt(attributes().agility()*attributes().strength()) +
            0.1*(attributes().dexterity() + attributes().agility());
}
