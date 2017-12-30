#ifndef UNITBASE_H
#define UNITBASE_H

#include "unitinfo.h"
#include "animatedobject.h"

class UnitBase : public AnimatedObject {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    using PositionType = Traits<Unit>::PositionType;
    using AngleType = Traits<Unit>::AngleType;
    using SizeType = Traits<Unit>::SizeType;

    UnitBase(const UnitInfo *info) : _info(info) {}

    const UnitInfo *unitInfo();

    void setX(PositionType x) { AnimatedObject::setX(x); }
    PositionType x() { return AnimatedObject::x(); }

    void setY(PositionType y) { AnimatedObject::setY(y); }
    PositionType y() { return AnimatedObject::y(); }

    void setAngle(AngleType angle);
    AngleType angle();

    SizeType size() { return _info->size(); }

private:

    static constexpr bool _using_radians();

    const UnitInfo *_info;
    SizeType _size;
};

#endif // UNITBASE_H
