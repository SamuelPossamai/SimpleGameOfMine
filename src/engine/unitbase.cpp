
#include <cmath>

#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>

#include "unitbase.h"

UnitBase::UnitBase(const UnitInfo *info) : _info(info), _obj(new AnimatedObject), _health(info->health()) {

    _obj->addAnimation(info->idleAnimation());

    for(UIntegerType i = 0; i < info->skills(); i++) _obj->addAnimation(info->skillAnimation(i));

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();

    effect->setOffset(0);
    effect->setBlurRadius(25);
    effect->setColor(QColor(255, 0, 0));
    effect->setEnabled(false);

    _obj->setGraphicsEffect(_effect = effect);

    _health_bar = new ProgressBarItem;

    _update_health_bar();
}

void UnitBase::setAngle(AngleType angle) {

    _obj->setRotation(angle*(_using_radians() ? 180/M_PI : 1));
}

UnitBase::AngleType UnitBase::angle() const {

    return _obj->rotation()*(_using_radians() ? M_PI/180 : 1);
}

void UnitBase::selectEffect() {

    _effect->setEnabled(true);
}

void UnitBase::removeSelectEffect() {

    _effect->setEnabled(false);
}

constexpr bool UnitBase::_using_radians() {

    return Traits<Unit>::angle_unit == Traits<Unit>::AngleUnitType::radians;
}

void UnitBase::addToScene(QGraphicsScene *scene) {

    scene->addItem(_obj);
    scene->addItem(_health_bar);
}

void UnitBase::removeFromScene(QGraphicsScene *scene) {

    scene->removeItem(_obj);
    scene->removeItem(_health_bar);
}

void UnitBase::setHealth(HealthType h) {

    if(h == _health) return;

    if(h > maxHealth()) _health = _info->health();
    else _health = h;

    _update_health_bar();
}

void UnitBase::_update_health_bar() {

    QRectF rect = _obj->boundingRect();

    _health_bar->setPos(x()/2 - 2.5*size()/4, y()/2 + rect.height()/3);
    _health_bar->setWidth(2.5*size());
    _health_bar->setHeight(10);

    _health_bar->setValue(100*health()/maxHealth());

    _health_bar->update();
}
