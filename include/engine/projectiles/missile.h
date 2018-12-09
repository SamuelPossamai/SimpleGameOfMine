
#ifndef PROJECTILE_MISSILE_H
#define PROJECTILE_MISSILE_H

#include "unit.h"
#include "enginemap.h"
#include "basicprojectile.h"

namespace projectile {

class Missile : public BasicProjectile {

public:

    Missile(EngineMap *m, const Unit *creator, AngleType dir, UIntegerType dur, SizeType s, SpeedType sp,
            DamageType damage, AngleType angular_speed, PointType pos = {0, 0}, AngleType angle = 0) :
        BasicProjectile(m, creator, dir, dur, s, sp, damage, pos, angle), _ang_speed(angular_speed) {}

    virtual ~Missile() override = default;

    virtual UIntegerType stepAction() override;

private:

    const AngleType _ang_speed;
};

} /* projectile */

#endif // PROJECTILE_MISSILE_H
