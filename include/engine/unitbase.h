#ifndef UNITBASE_H
#define UNITBASE_H

#include <QProgressBar>

#include "unitinfo.h"
#include "animatedobject.h"
#include "animation/progressbaritem.h"

class UnitBase {

public:

    using PointType = Traits<Unit>::PointType;

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    using PositionType = Traits<Unit>::PositionType;
    using AngleType = Traits<Unit>::AngleType;
    using SizeType = Traits<Unit>::SizeType;

    UnitBase(const UnitInfo *info);

    const UnitInfo *unitInfo() const { return _info; }

    void setX(PositionType x) { _x = x; }
    PositionType x() const { return _x; }

    void setY(PositionType y) { _y = y; }
    PositionType y() const { return _y; }

    void setPos(PositionType x, PositionType y) { _x = x; _y = y;  }
    void setPos(PointType p) { setPos(p.x, p.y); }
    PointType pos() const { return { x(), y() }; }

    void setAngle(AngleType angle);
    AngleType angle() const;

    SizeType size() const { return _info->size(); }

    void setHealth(HealthType health);
    HealthType health() const { return _health; }

    HealthType maxHealth() const { return _info->health(); }

private:

    static constexpr bool _using_radians();

    const UnitInfo *_info;
    SizeType _size;

    HealthType _health;

    PositionType _x, _y;
    AngleType _angle;
};

#endif // UNITBASE_H
