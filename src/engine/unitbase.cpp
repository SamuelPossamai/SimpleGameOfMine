
#include <cmath>

#include "unitbase.h"

UnitBase::UnitBase(const UnitInfo *info, EngineMap *m, const Attributes& attr, UIntegerType level) :
    EngineObject(m, info->size(attr, level), info->speed(attr, level)), _info(info), _health(info->health(attr, level)),
    _energy(info->energy(attr, level)), _special(0), _rage(0), _level(level), _attr(attr) {

}


