
#include <cmath>

#include "unitbase.h"

UnitBase::UnitBase(const UnitInfo *info, EngineMap *m) :
    EngineObject(m, info->size(), info->speed()), _info(info), _health(info->health()), _energy(info->energy()) {

}

void UnitBase::setHealth(HealthType h) {

    if(h == _health) return;

    if(h > maxHealth()) _health = _info->health();
    else _health = h;
}

