
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

    _info->addSkill(new skill::Walk(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
    _info->addSkill(new skill::Evade, QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    _info->addSkill(new skill::Thrust(12, 90), QPixmap(":/x_simbol.png").scaled(50, 50));

    _info->setSize(22);
    _info->setHealth(10);

    return _info;
}

} /* namespace creature */
