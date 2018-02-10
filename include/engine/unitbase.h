#ifndef UNITBASE_H
#define UNITBASE_H

#include <QProgressBar>

#include "unitinfo.h"
#include "animatedobject.h"

class UnitBase {

public:

    using PointType = Traits<Unit>::PointType;

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    using PositionType = Traits<Unit>::PositionType;
    using AngleType = Traits<Unit>::AngleType;
    using SizeType = Traits<Unit>::SizeType;

    UnitBase(const UnitInfo *info, QWidget *);

    ~UnitBase() { delete _obj; }

    const UnitInfo *unitInfo() const { return _info; }

    void setX(PositionType x) { _obj->setX(x); _update_health_bar(); }
    PositionType x() { return _obj->x(); _update_health_bar(); }

    void setY(PositionType y) { _obj->setY(y); _update_health_bar(); }
    PositionType y() { return _obj->y(); _update_health_bar(); }

    PointType pos() { return { x(), y() }; }

    void setAngle(AngleType angle);
    AngleType angle();

    SizeType size() { return _info->size(); }

    void addToScene(QGraphicsScene *scene);
    void removeFromScene(QGraphicsScene *scene);

    void animationStep() { _obj->step(); }

    void startSkillAnimation(UIntegerType skill) { _obj->selectAnimation(skill + 1); }
    void endSkillAnimation() { _obj->selectAnimation(_obj->idleAnimation()); }

    void selectEffect();
    void removeSelectEffect();

    void setHealth(HealthType health) { if(health > maxHealth()) _health = _info->health(); else _health = health; }
    HealthType health() const { return _health; }

    HealthType maxHealth() const { return _info->health(); }

private:

    void _update_health_bar();

    static constexpr bool _using_radians();

    const UnitInfo *_info;
    SizeType _size;

    AnimatedObject *_obj;
    QGraphicsEffect *_effect;

    HealthType _health;

    QProgressBar *_health_bar;
};

#endif // UNITBASE_H
