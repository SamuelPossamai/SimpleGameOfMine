
#include <cmath>

#include "controllers/human.h"

using namespace controller;

Human *Human::_controller = nullptr;

UIntegerType Human::chooseSkill(const Unit *unit, const Map *, UserInterface *i) {

    return i->askSkill(unit);
}

std::optional<Human::AngleType> Human::chooseAngle(const Unit *unit, const Map *, UserInterface *i) {

    return i->askAngle(unit);
}
