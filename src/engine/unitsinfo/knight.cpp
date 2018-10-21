
#include <cmath>

#include "imagecolorchange.h"
#include "unitsinfo/knight.h"
#include "skills/walk.h"
#include "skills/basicattack.h"
#include "skills/rage.h"
#include "skills/knightblock.h"

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

    utility::ImageColorChange icch;

    icch.addChInterval({0, 120}, {200, 256}, {200, 256}, QColor("#c0c0c0"));
    icch.addChInterval({0, 30}, {0, 30}, {220, 256}, QColor("#808080"));

    QImage im(":/magic_shield.png");

    icch.changeImage(im);

    addSkill(skill::KnightBlock::getSkill(), QPixmap::fromImage(im));

    calculateInfo();
}

Knight::SpeedType Knight::speedCalculate() const {

    return 45 + 0.7*std::sqrt(attributes().agility()*attributes().strength()) +
            0.1*(attributes().dexterity() + attributes().agility());
}
