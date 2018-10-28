
#include <cmath>

#include "engine/unit.h"
#include "engine/enginemap.h"
#include "utility/random.h"
#include "controllers/ai/zucontroller.h"

using namespace controller::AI;
using namespace utility;

ZuController *ZuController::_controller;

UIntegerType ZuController::chooseSkill(const Unit *, const Map *, UserInterface *) {

    return 0;
}

std::optional<ZuController::AngleType> ZuController::chooseAngle(const Unit *u, const Map *m, UserInterface *) {

    const Unit *closer_enemy = m->closerEnemy(u);

    AngleType base_angle = atan2(closer_enemy->y() - u->y(), closer_enemy->x() - u->x());

    return utility::Random::realDistribution(-0.1, 0.1)*M_PI + base_angle;
}


