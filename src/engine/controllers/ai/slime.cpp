
#include <cmath>

#include "controllers/ai/slime.h"
#include "map.h"
#include "unit.h"

using namespace controller::AI;

UIntegerType Slime::chooseSkill(const Unit *u, const Map *m, UserInterface *) {

    auto closer_enemy = m->closerEnemy(u);

    if(closer_enemy == nullptr) return 0;

    if(m->unitsDistance(u, closer_enemy) < 180) return 2;

    return 0;
}

Slime::AngleType Slime::chooseAngle(const Unit *u, const Map *m, UserInterface *) {

    const Unit *closer_enemy = m->closerEnemy(u);

    return atan2(closer_enemy->y() - u->y(), closer_enemy->x() - u->x());
}

