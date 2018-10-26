
#include <cmath>

#include "unitbase.h"

UnitBase::UnitBase(const UnitInfo *info, EngineMap *m, const Attributes& attr, UIntegerType level) :
    EngineObject(m, info->size(attr, level), info->speed(attr, level)), _info(info), _health(info->health(attr, level)),
    _energy(info->energy(attr, level)), _level(level), _attr(attr) {

}

void UnitBase::setHealth(HealthType h) {

    if(h == _health) return;

    if(h > maxHealth()) _health = maxHealth();
    else _health = h;
}

