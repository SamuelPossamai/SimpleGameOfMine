
#include <cmath>

#include "engineobjectbase.h"

EngineObjectBase::~EngineObjectBase() {

}

void EngineObjectBase::setAngle(AngleType angle) {

    angle = std::fmod(angle, 2*M_PI);
    if(angle < 0) angle += 2*M_PI;
    _angle = angle;
}

