
#include <cmath>

#include <engine/unit.h>
#include <utility/random.h>

#include "controllers/ai/pacifistslime.h"

using namespace controller::AI;
using namespace utility;

PacifistSlime *PacifistSlime::_controller;

UIntegerType PacifistSlime::chooseSkill(const Unit *u, const Map *m, UserInterface *i) {

    if(u->health() == u->maxHealth()) return 0;

    return Slime::chooseSkill(u, m, i);
}

std::optional<PacifistSlime::AngleType> PacifistSlime::chooseAngle(const Unit *u, const Map *m, UserInterface *i) {

    if(u->health() == u->maxHealth()) return Random::realDistribution(0, 2*M_PI);

    return Slime::chooseAngle(u, m, i);
}


