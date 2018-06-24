
#include <QGraphicsDropShadowEffect>

#include "basicunitgraphicitem.h"
#include "animatedobject.h"
#include "progressbaritem.h"

BasicUnitGraphicItem::BasicUnitGraphicItem(Unit *u) : UnitAnimationItem(u), _obj(new AnimatedObject),
    _health_bar(new ProgressBarItem) {

    _obj->addAnimation(u->unitInfo()->idleAnimation());

    for(UIntegerType i = 0; i < u->unitInfo()->skills(); i++) _obj->addAnimation(u->unitInfo()->skillAnimation(i));

    auto *effect = new QGraphicsDropShadowEffect;

    effect->setOffset(0);
    effect->setBlurRadius(25);
    effect->setColor(QColor(255, 0, 0));
    effect->setEnabled(false);

    _health_bar->setWidth(2.5*u->size());
    _health_bar->setHeight(10);

    _obj->setGraphicsEffect(_select_effect = effect);
}

void BasicUnitGraphicItem::unitMoved() {

    _obj->setPos(unit()->x(), unit()->y());
    _health_bar->setPos(unit()->x()/2 - 2.5*unit()->size()/4, unit()->y()/2 + _obj->boundingRect().height()/3);
}
