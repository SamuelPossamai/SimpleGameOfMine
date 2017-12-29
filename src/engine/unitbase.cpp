
#include <cmath>

#include "unitbase.h"

void UnitBase::setAngle(AngleType angle) {

    AnimatedObject::setRotation(angle*(_using_radians() ? 180/M_PI : 1));
}

UnitBase::AngleType UnitBase::angle() {

    return AnimatedObject::rotation()*(_using_radians() ? M_PI/180 : 1);
}


constexpr bool UnitBase::_using_radians() {

    return Traits<Unit>::angle_unit == Traits<Unit>::AngleUnitType::radians;
}
