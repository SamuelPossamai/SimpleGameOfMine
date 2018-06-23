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

    ~UnitBase() { delete _obj; delete _health_bar; }

    const UnitInfo *unitInfo() const { return _info; }

    void setX(PositionType x) { _obj->setX(x); _update_health_bar(); }
    PositionType x() const { return _obj->x(); }

    void setY(PositionType y) { _obj->setY(y); _update_health_bar(); }
    PositionType y() const { return _obj->y(); }

    void setPos(PositionType x, PositionType y) { _obj->setX(x); _obj->setY(y); _update_health_bar(); }
    void setPos(PointType p) { setPos(p.x, p.y); }
    PointType pos() const { return { x(), y() }; }

    void setAngle(AngleType angle);
    AngleType angle() const;

    SizeType size() const { return _info->size(); }

    void addToScene(QGraphicsScene *scene);
    void removeFromScene(QGraphicsScene *scene);

    void animationStep() { _obj->step(); }

    void startSkillAnimation(UIntegerType skill) { _obj->selectAnimation(skill + 1); }
    void endSkillAnimation() { _obj->selectAnimation(_obj->idleAnimation()); }

    void selectEffect();
    void removeSelectEffect();

    void setHealth(HealthType health);
    HealthType health() const { return _health; }

    HealthType maxHealth() const { return _info->health(); }

    void showAnimation() { _obj->show(); _health_bar->show(); }
    void hideAnimation() { _obj->hide(); _health_bar->hide(); }

private:

    void _update_health_bar();

    static constexpr bool _using_radians();

    const UnitInfo *_info;
    SizeType _size;

    AnimatedObject *_obj;
    QGraphicsEffect *_effect;

    HealthType _health;

    ProgressBarItem *_health_bar;
};

#endif // UNITBASE_H
