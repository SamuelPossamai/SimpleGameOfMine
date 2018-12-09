
#include "projectiles/missile.h"

using namespace projectile;

UIntegerType Missile::stepAction() {

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
