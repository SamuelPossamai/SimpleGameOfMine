
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <limits>

#include <QtGlobal>

#include "engineobject.h"

class Projectile : public EngineObject {

public:

    Projectile(Map *m, AngleType dir, UIntegerType dur, SizeType s, SpeedType sp, PointType pos = {0, 0}, AngleType angle = 0) :
        EngineObject(m, s, sp, pos, angle), _to_next_action(1), _dir(dir), _durability(dur) {}

    virtual ~Projectile() override {}

    bool act() final;

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

    virtual UIntegerType stepAction() { return std::numeric_limits<UIntegerType>::max(); }
    virtual void collideAction(Map *m, EngineObject *obj) { Q_UNUSED(m); Q_UNUSED(obj); }

private:

    UIntegerType _to_next_action;
    AngleType _dir;

    UIntegerType _durability;
};

#endif // PROJECTILE_H
