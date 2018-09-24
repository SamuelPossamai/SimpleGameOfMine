
#include <cmath>

#include <utility/random.h>

#include "controllers/ai/timidslime.h"
#include "map.h"
#include "unit.h"

using namespace controller::AI;

TimidSlime *TimidSlime::_controller = nullptr;

std::optional<TimidSlime::AngleType> TimidSlime::chooseAngle(const Unit *u, const Map *m, UserInterface *) {

    const Unit *closer_enemy = m->closerEnemy(u);

    AngleType base_angle = atan2(closer_enemy->y() - u->y(), closer_enemy->x() - u->x());

    if(m->objectsDistance(u, closer_enemy) < 200) base_angle += M_PI;

    return utility::Random::realDistribution(-0.1, 0.1)*M_PI + base_angle;
}

