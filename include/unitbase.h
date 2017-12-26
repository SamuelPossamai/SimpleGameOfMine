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


    void angle(IntegerType angle) { _angle = angle; }
    IntegerType angle() { return _angle; }

    IntegerType x() { return _x; }
    IntegerType y() { return _y; }

private:

    UnitInfo *_info;
    IntegerType _x, _y, _angle;
};

#endif // UNITBASE_H
