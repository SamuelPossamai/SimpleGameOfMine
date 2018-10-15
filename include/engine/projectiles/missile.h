
#ifndef MISSILE_H
#define MISSILE_H

#include <iostream>

#include "unit.h"
#include "enginemap.h"
#include "basicprojectile.h"

#include <iostream>

namespace projectile {

class Missile : public BasicProjectile {

public:

    Missile(EngineMap *m, const Unit *creator, AngleType dir, UIntegerType dur, SizeType s, SpeedType sp,
            DamageType damage, AngleType angular_speed, PointType pos = {0, 0}, AngleType angle = 0) :
        BasicProjectile(m, creator, dir, dur, s, sp, damage, pos, angle), _ang_speed(angular_speed) {}

    virtual ~Missile() override = default;

    virtual UIntegerType stepAction() override {

        auto target = map()->closerEnemy(pos(), creator()->team());

        AngleType t_angle = std::atan2(target->y() - y(), target->x() - x());

        AngleType new_value = t_angle;

        std::pair<AngleType, bool> diff_and_dir = EngineMap::angleDiffAndDir(t_angle, angle());

        AngleType diff = diff_and_dir.first;

        if(diff > _ang_speed) {

            new_value = angle();
            if(diff > 3*M_PI/4 || diff_and_dir.second) new_value += _ang_speed;
            else new_value -= _ang_speed;
        }

        setAngle(new_value);
        setDirection(new_value);

        return 3;
    }

private:

    const AngleType _ang_speed;
};

} /* projectile */

#endif // MISSILE_H
