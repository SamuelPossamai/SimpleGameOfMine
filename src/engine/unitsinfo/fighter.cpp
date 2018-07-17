
#include "animation.h"
#include "unitsinfo/fighter.h"
#include "skills/walk.h"

namespace unitsinfo {

Fighter *Fighter::_info = nullptr;

Fighter *Fighter::getInfo() {

    if(_info) return _info;

    _info = new Fighter;

    _info->addSkill(skill::Walk::getSkill(10, 140), QPixmap(":/wing_boot.png").scaled(50, 50));
    _info->addSkill(skill::Walk::getSkill(60, 0), QPixmap(":/x_simbol.png").scaled(50, 50));

    _info->setSize(20);
    _info->setHealth(20);
    _info->setSpeed(100);

    return _info;
}

} /* namespace creature */
