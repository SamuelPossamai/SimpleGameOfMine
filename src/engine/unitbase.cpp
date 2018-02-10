
#include <cmath>

#include <QGraphicsDropShadowEffect>
#include <QGraphicsScene>

#include "unitbase.h"

UnitBase::UnitBase(const UnitInfo *info, QWidget *w) : _info(info), _obj(new AnimatedObject), _health(info->health()) {

    _obj->addAnimation(info->idleAnimation());

    for(UIntegerType i = 0; i < info->skills(); i++) _obj->addAnimation(info->skillAnimation(i));

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();

    effect->setOffset(0);
    effect->setBlurRadius(25);
    effect->setColor(QColor(255, 0, 0));
    effect->setEnabled(false);

    _obj->setGraphicsEffect(_effect = effect);

    _health_bar = new QProgressBar(w);

    QPalette p = _health_bar->palette();
    p.setColor(QPalette::Highlight, Qt::red);

    _health_bar->setPalette(p);

    _update_health_bar();
}

void UnitBase::setAngle(AngleType angle) {

    _obj->setRotation(angle*(_using_radians() ? 180/M_PI : 1));
}

UnitBase::AngleType UnitBase::angle() {

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
}

void UnitBase::removeFromScene(QGraphicsScene *scene) {

    scene->removeItem(_obj);
}

void UnitBase::_update_health_bar() {

    QRectF rect = _obj->boundingRect();

    _health_bar->setGeometry( QRect( x() + rect.x() + (RealType(rect.width()) - size())/2,
                                     y() - rect.y(), 2.5*size(), size() ) );

    _health_bar->setValue(100*health()/maxHealth());
}
