
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <limits>

#include <QtGlobal>

#include "engineobject.h"

class Projectile : public EngineObject {

public:

    using DamageType = Traits<Unit>::AttackType;

    Projectile(Map *m, const Unit *creator, AngleType dir, UIntegerType dur,
               SizeType s, SpeedType sp, PointType pos = {0, 0}, AngleType angle = 0) :
        EngineObject(m, s, sp, pos, angle), _to_next_action(1), _dir(dir), _durability(dur), _creator(creator) {}

    virtual ~Projectile() override {}

    bool act() final;

    void setDirection(AngleType angle) { _dir = angle; }

    void destroy() { _durability = 0; map()->removeObject(this); }

    bool decreaseDurability(UIntegerType v) {

        if(v >= _durability){

            destroy();
            return false;
        }

        _durability -= v;
        return true;
    }

    UIntegerType durability() const { return _durability; }

    const Unit *creator() const { return _creator; }

    virtual UIntegerType stepAction() { return std::numeric_limits<UIntegerType>::max(); }
    virtual void collideAction(Map *m, EngineObject *obj) { Q_UNUSED(m); Q_UNUSED(obj); }

private:

    UIntegerType _to_next_action;
    AngleType _dir;

    UIntegerType _durability;
    const Unit * const _creator;
};

#endif // PROJECTILE_H
