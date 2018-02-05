
#include <cmath>

#include <QGraphicsScene>

#include "unitbase.h"

UnitBase::UnitBase(const UnitInfo *info) : _info(info), _obj(new AnimatedObject) {

    _obj->addAnimation(info->idleAnimation());

    for(UIntegerType i = 0; i < info->skills(); i++) _obj->addAnimation(info->skillAnimation(i));
}

void UnitBase::setAngle(AngleType angle) {

    _obj->setRotation(angle*(_using_radians() ? 180/M_PI : 1));
}

UnitBase::AngleType UnitBase::angle() {

    return _obj->rotation()*(_using_radians() ? M_PI/180 : 1);
}


constexpr bool UnitBase::_using_radians() {

    return Traits<Unit>::angle_unit == Traits<Unit>::AngleUnitType::radians;
}

void UnitBase::addToScene(QGraphicsScene *scene) {

    scene->addItem(_obj);
}

void UnitBase::removeFromScene(QGraphicsScene *scene) {

    scene->removeItem(_obj);
}


