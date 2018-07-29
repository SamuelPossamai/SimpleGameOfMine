
#include <cmath>

#include <QGraphicsDropShadowEffect>

#include "unitanimations/basicunitgraphicitem.h"
#include "progressbaritem.h"

namespace unitanimation {

BasicUnitGraphicItem::BasicUnitGraphicItem(Unit *u) : UnitAnimationItem(u), _obj(new AnimatedObject),
    _health_bar(new ProgressBarItem), _energy_bar(nullptr) {

    if(u->maxEnergy() > 0) _energy_bar = new ProgressBarItem;

    auto *effect = new QGraphicsDropShadowEffect;

    effect->setOffset(0);
    effect->setBlurRadius(25);
    effect->setColor(QColor(255, 0, 0));
    effect->setEnabled(false);

    _health_bar->setWidth(2.5*u->size());
    _health_bar->setHeight(10);

    if(_energy_bar) {

        _energy_bar->setWidth(_health_bar->width());
        _energy_bar->setHeight(_health_bar->height());
        _energy_bar->setFgColor(Qt::blue);
    }

    _obj->setGraphicsEffect(_select_effect = effect);
}

void BasicUnitGraphicItem::unitMoved() {

    _obj->setPos(unit()->x(), unit()->y());
    _health_bar->setPos(unit()->x()/2 - 2.5*unit()->size()/4, unit()->y()/2 + _obj->boundingRect().height()/3);
    if(_energy_bar) {

        auto p = _health_bar->pos();
        p.setY(p.y() + 5);
        _energy_bar->setPos(p);
    }
}

void BasicUnitGraphicItem::unitRotated() {

    _obj->setRotation(unit()->angle()*180/M_PI);
}

void BasicUnitGraphicItem::selectEffect() {

    _select_effect->setEnabled(true);
}

void BasicUnitGraphicItem::removeSelectEffect() {

    _select_effect->setEnabled(false);
}

void BasicUnitGraphicItem::unitSkillStarted() {

    _obj->selectAnimation(unit()->skillId() + 1);
}

void BasicUnitGraphicItem::unitSkillFinished() {

    _obj->selectAnimation(_obj->idleAnimation());
}

void BasicUnitGraphicItem::unitSkillAdvance() {

    _obj->step();
}

void BasicUnitGraphicItem::unitHealthChanged() {

    _health_bar->setValue(100*unit()->health()/unit()->maxHealth());
}

void BasicUnitGraphicItem::unitEnergyConsumed() {

    _energy_bar->setValue(100*unit()->energy()/unit()->maxEnergy());
}

void BasicUnitGraphicItem::_add_animations(const Animation& a) {

    _obj->addAnimation(a);
}

} /* namespace unitanimation */
