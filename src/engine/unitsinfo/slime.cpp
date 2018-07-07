
#include "animation.h"
#include "unitsinfo/slime.h"
#include "skills/walk.h"
#include "skills/evade.h"
#include "skills/thrust.h"

namespace unitsinfo {

static UnitInfo *__slime_info__ = nullptr;

static void __slime_init__();

UnitInfo *slimeInfo() {

    if(__slime_info__ == nullptr) __slime_init__();

    return __slime_info__;
}

void __slime_init__() {

    __slime_info__ = new UnitInfo;

    UnitInfo & __slime_info__ = *unitsinfo::__slime_info__;

    __slime_info__.addSkill(new skill::Walk(10, 100), QPixmap(":/wing_boot.png").scaled(50, 50));
    __slime_info__.addSkill(new skill::Evade, QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    __slime_info__.addSkill(new skill::Thrust(12, 90), QPixmap(":/x_simbol.png").scaled(50, 50));

    __slime_info__.setSize(22);
    __slime_info__.setHealth(10);
}

} /* namespace creature */
