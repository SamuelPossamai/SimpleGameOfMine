
#include "controllers/human.h"
#include "battleengine.h"
#include "unit.h"

using namespace controller;

UIntegerType Human::choose(Unit *, Map *, BattleEngine *e) {

    return e->askSkill();
}
