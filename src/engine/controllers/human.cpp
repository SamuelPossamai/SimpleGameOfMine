
#include <cmath>

#include "controllers/human.h"
#include "battlewidget.h"
#include "battleengine.h"
#include "unit.h"

using namespace controller;

UIntegerType Human::chooseSkill(const Unit *, const Map *, UserInterface *i) {

    return i->askSkill();
}

Human::AngleType Human::chooseAngle(const Unit *, const Map *, UserInterface *i) {

    return i->askAngle();
}
