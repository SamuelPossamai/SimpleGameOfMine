
#include <cmath>

#include <engine/unit.h>
#include <engine/map.h>
#include <utility/random.h>

#include "controllers/ai/monsterplant.h"

using namespace controller::AI;
using namespace utility;

MonsterPlant *MonsterPlant::_controller;

UIntegerType MonsterPlant::chooseSkill(const Unit *u, const Map *m, UserInterface *) {

    return m->objectsDistance(u, m->closerEnemy(u)) < 110 ? 1 : 0;
}

std::optional<MonsterPlant::AngleType> MonsterPlant::chooseAngle(const Unit *u, const Map *m, UserInterface *) {

    const Unit *closer_enemy = m->closerEnemy(u);

    AngleType base_angle = atan2(closer_enemy->y() - u->y(), closer_enemy->x() - u->x());

    return utility::Random::realDistribution(-0.1, 0.1)*M_PI + base_angle;
}


