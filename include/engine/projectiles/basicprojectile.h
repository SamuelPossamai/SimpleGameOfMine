
#ifndef PROJECTILE_BASICPROJECTILE_H
#define PROJECTILE_BASICPROJECTILE_H

#include "projectile.h"

namespace projectile {

class BasicProjectile : public Projectile {

public:

    BasicProjectile(EngineMap *m, const Unit *creator, AngleType dir, UIntegerType dur,
                    SizeType s, SpeedType sp, DamageType damage, PointType pos = {0, 0}, AngleType angle = 0) :
        Projectile(m, creator, dir, dur, s, sp, pos, angle), _damage(damage) {}

    virtual ~BasicProjectile() override = default;

    virtual void collideAction(Map *m, EngineObject *obj) override;

private:

    DamageType _damage;
};

} /* projectile */

#endif // PROJECTILE_BASICPROJECTILE_H
