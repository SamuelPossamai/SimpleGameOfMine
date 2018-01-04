
#include "battleengine.h"
#include "unit.h"

BattleEngine::~BattleEngine() {

    for(UIntegerType i = 0; i < _map.units(); i++) delete _map.unitAccess(i);
}

void BattleEngine::addUnit(const UnitInfo *unit_info, UIntegerType team) {

    _map.addUnit(new Unit(unit_info, team));
}
