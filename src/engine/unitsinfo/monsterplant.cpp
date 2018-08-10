
#include <engine/skills/walk.h>
#include <engine/skills/plantareaattack.h>

#include "unitsinfo/monsterplant.h"

using namespace unitsinfo;

OneCopyMemoryManager<MonsterPlant> MonsterPlant::_memmanager;

MonsterPlant::MonsterPlant(UIntegerType level) : _level(level) {

    addSkill(skill::Walk::MemoryInterface::dependentGet(15, 80), QPixmap(":/wing_boot.png").scaled(50, 50));
    addSkill(skill::PlantAreaAttack::getSkill());

    setSize(30);
    setHealth(400 + 35*level);
    setBaseAttack(15 + 1.2*level);
    setSpeed(60 + level);
}

MonsterPlant::~MonsterPlant() {

    skill::Walk::MemoryInterface::noLongerDepend(15, 80);
}
