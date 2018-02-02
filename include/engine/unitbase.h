#ifndef UNITBASE_H
#define UNITBASE_H

#include "unitinfo.h"
#include "animatedobject.h"

class UnitBase {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    using PositionType = Traits<Unit>::PositionType;
    using AngleType = Traits<Unit>::AngleType;
    using SizeType = Traits<Unit>::SizeType;

    UnitBase(const UnitInfo *info);

    ~UnitBase() { delete _obj; }

    const UnitInfo *unitInfo() const { return _info; }

    void setX(PositionType x) { _obj->setX(x); }
    PositionType x() { return _obj->x(); }

    void setY(PositionType y) { _obj->setY(y); }
    PositionType y() { return _obj->y(); }

    void setAngle(AngleType angle);
    AngleType angle();

    SizeType size() { return _info->size(); }

    void addToScene(QGraphicsScene *scene);
    void removeFromScene(QGraphicsScene *scene);

    void animationStep() { _obj->step(); }

private:

    static constexpr bool _using_radians();

    const UnitInfo *_info;
    SizeType _size;

    AnimatedObject *_obj;
};

#endif // UNITBASE_H
