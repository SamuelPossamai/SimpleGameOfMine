
#include "animation.h"
#include "unitsinfo/slime.h"
#include "skills/walk.h"
#include "skills/evade.h"
#include "skills/thrust.h"

namespace unitsinfo {

Slime *Slime::_info = nullptr;

Slime *Slime::getInfo() {

    if(_info) return _info;

    _info = new Slime;

    _info->addSkill(skill::Walk::getSkill(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
    _info->addSkill(skill::Evade::getSkill(), QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    _info->addSkill(skill::Thrust::getSkill(12, 90), QPixmap(":/x_simbol.png").scaled(50, 50));

    _info->setSize(22);
    _info->setHealth(10);
    _info->setSpeed(100);

    return _info;
}

} /* namespace creature */
