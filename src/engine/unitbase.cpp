
#include <cmath>

#include "unitbase.h"

UnitBase::UnitBase(const UnitInfo *info) : _info(info), _health(info->health()), _energy(info->energy()) {

}

void UnitBase::setAngle(AngleType angle) {

    angle = fmod(angle, 2*M_PI);
    if(angle < 0) angle += 2*M_PI;
    _angle = angle*(_using_radians() ? 180/M_PI : 1);
}

UnitBase::AngleType UnitBase::angle() const {

    return _angle*(_using_radians() ? M_PI/180 : 1);
}

constexpr bool UnitBase::_using_radians() {

    return Traits<Unit>::angle_unit == Traits<Unit>::AngleUnitType::radians;
}

void UnitBase::setHealth(HealthType h) {

    if(h == _health) return;

    if(h > maxHealth()) _health = _info->health();
    else _health = h;
}

