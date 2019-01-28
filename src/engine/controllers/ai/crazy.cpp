
#include <cmath>

#include <engine/unit.h>
#include <utility/random.h>

#include "controllers/ai/crazy.h"

using namespace controller::AI;
using namespace utility;

Crazy *Crazy::_controller;

UIntegerType Crazy::chooseSkill(const Unit *u, const Map *, UserInterface *) {

    return Random::uniformIntDistribution(0, u->skillsAmount() - 1);
}

std::optional<Crazy::AngleType> Crazy::chooseAngle(const Unit *, const Map *, UserInterface *) {

    return Random::realDistribution(0, 2*M_PI);
}


