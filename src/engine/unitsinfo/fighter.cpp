
#include "animation.h"
#include "unitsinfo/fighter.h"
#include "skills/walk.h"

namespace unitsinfo {

static UnitInfo *__fighter_info__ = nullptr;

static void __fighter_init__();

UnitInfo *fighterInfo() {

    if(__fighter_info__ == nullptr) __fighter_init__();

    return __fighter_info__;
}

void __fighter_init__() {

    __fighter_info__ = new UnitInfo;

    UnitInfo & __fighter_info__ = *unitsinfo::__fighter_info__;

    __fighter_info__.addSkill(new skill::Walk(10, 140), QPixmap(":/wing_boot.png").scaled(50, 50));
    __fighter_info__.addSkill(new skill::Walk(60, 0), QPixmap(":/x_simbol.png").scaled(50, 50));

    __fighter_info__.setSize(20);
    __fighter_info__.setHealth(20);
}

} /* namespace creature */
