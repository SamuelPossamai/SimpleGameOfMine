
#include <cmath>

#include <utility/random.h>

#include "controllers/ai/slime.h"
#include "enginemap.h"
#include "unit.h"

using namespace controller::AI;

Slime *Slime::_controller = nullptr;

UIntegerType Slime::chooseSkill(const Unit *u, const EngineMap *m, UserInterface *) {

    auto closer_enemy = m->closerEnemy(u);

    if(closer_enemy == nullptr) return 1;

    EngineMap::PositionType dist = m->objectsDistance(u, closer_enemy);
    if(dist < 230) {

        if(dist < 30) return 2;

        auto angle1 = atan2(RealType(closer_enemy->y()) - u->y(), RealType(closer_enemy->x()) - u->x());
        auto angle2 = u->angle();

        if(EngineMap::angleDiff(angle1, angle2) < M_PI/4) return 2;
    }

    return 0;
}

std::optional<Slime::AngleType> Slime::chooseAngle(const Unit *u, const Map *m, UserInterface *) {

    const Unit *closer_enemy = m->closerEnemy(u);

    AngleType base_angle = atan2(closer_enemy->y() - u->y(), closer_enemy->x() - u->x());

    if(m->objectsDistance(u, closer_enemy) < 50) base_angle += M_PI;

    return utility::Random::realDistribution(-0.1, 0.1)*M_PI + base_angle;
}

