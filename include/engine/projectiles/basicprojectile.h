
#ifndef BASICPROJECTILE_H
#define BASICPROJECTILE_H

#include "projectile.h"

namespace projectile {

class BasicProjectile : public Projectile {

public:

    BasicProjectile(Map *m, AngleType dir, UIntegerType dur, SizeType s, SpeedType sp, DamageType damage,
                    PointType pos = {0, 0}, AngleType angle = 0) :
        Projectile(m, dir, dur, s, sp, pos, angle), _damage(damage) {}

    virtual ~BasicProjectile() override {}

    virtual void collideAction(Map *m, EngineObject *obj) override;

private:

    DamageType _damage;
};

} /* projectile */

#endif // BASICPROJECTILE_H
