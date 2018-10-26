
#include <engine/skills/walk.h>
#include <engine/skills/plantareaattack.h>

#include "unitsinfo/monsterplant.h"

using namespace unitsinfo;

MonsterPlant *MonsterPlant::_info = nullptr;

MonsterPlant::MonsterPlant() {

    addSkill(skill::Walk::MemoryInterface::dependentGet(15, 80), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::PlantAreaAttack::getSkill());
}

MonsterPlant::~MonsterPlant() {

    skill::Walk::MemoryInterface::noLongerDepend(15, 80);
}
