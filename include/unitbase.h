#ifndef UNITBASE_H
#define UNITBASE_H

#include "unitinfo.h"

class UnitBase {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    UnitBase(UnitInfo *info) : _info(info) {}

    const UnitInfo *unitInfo();

    void x(IntegerType x) { _x = x; }
    void y(IntegerType y) { _y = y; }

    IntegerType x() { return _x; }
    IntegerType y() { return _y; }

private:

    UnitInfo *_info;
    IntegerType _x, _y;
};

#endif // UNITBASE_H
