
#include "battleengine.h"
#include "unit.h"

void BattleEngine::addUnit(const UnitInfo *unit_info) {

    _map.addUnit(new Unit(unit_info));
}
