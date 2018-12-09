
#include <cmath>

#include <QGraphicsDropShadowEffect>

#include <utility/imagecolorchange.h>
#include <engine/effects/lastescape.h>
#include <engine/effects/regeneration.h>
#include <engine/effects/adrenaline.h>
#include <engine/effects/magicshield.h>
#include <engine/effects/shield.h>

#include "animationitens/unit/basicunitgraphicitem.h"
#include "partialimageitem.h"
#include "progressbaritem.h"

using namespace unitanimation;

std::map<std::type_index, QImage> BasicUnitGraphicItem::_effect_images;

BasicUnitGraphicItem::BasicUnitGraphicItem(Unit *u) : UnitAnimationItem(u), _obj(new AnimatedObject),
    _health_bar(new ProgressBarItem), _energy_bar(nullptr), _special_bar(nullptr), _rage_bar(nullptr) {

    if(_effect_images.empty()) _init();

    auto *effect = new QGraphicsDropShadowEffect;

    effect->setOffset(0);
    effect->setBlurRadius(25);
    effect->setColor(QColor(255, 0, 0));
    effect->setEnabled(false);

    _init_bar(_health_bar, Qt::red, 2.5*u->size(), 10);

    if(u->maxEnergy() > 0) {

        _energy_bar = new ProgressBarItem;
        _init_bar(_energy_bar, Qt::blue, _health_bar->width(), _health_bar->height());
    }
    if(u->maxSpecial() > 0) {

        _special_bar = new ProgressBarItem;
        _init_bar(_special_bar, Qt::green, _health_bar->width(), _health_bar->height(), 0);
    }
    if(u->maxRage() > 0) {

        _rage_bar = new ProgressBarItem;
        _init_bar(_rage_bar, QColor(0xff, 0xa5, 0x00), _health_bar->width(), _health_bar->height(), 0);
    }

    _obj->setGraphicsEffect(_select_effect = effect);

    for(auto p : unit()->effects()) _add_effect_item(p.first);
}

BasicUnitGraphicItem::~BasicUnitGraphicItem() {

    delete _obj;
    delete _health_bar;
    if(_energy_bar) delete _energy_bar;
    if(_special_bar) delete _special_bar;
    if(_rage_bar) delete _rage_bar;

    for(auto p : _effect_itens) delete p.second;
}

void BasicUnitGraphicItem::addToScene(QGraphicsScene *scene) {

    scene->addItem(_obj);

    ProgressBarItem *bars[] = { _health_bar, _energy_bar, _special_bar, _rage_bar };
    for(auto *bar : bars) {
        if(bar) scene->addItem(bar);
    }

    for(auto p : _effect_itens) scene->addItem(p.second);
}

void BasicUnitGraphicItem::removeFromScene() {

    scene()->removeItem(_obj);

    ProgressBarItem *bars[] = { _health_bar, _energy_bar, _special_bar, _rage_bar };
    for(auto *bar : bars) {
        if(bar) scene()->removeItem(bar);
    }

    for(auto p : _effect_itens) scene()->removeItem(p.second);
}

void BasicUnitGraphicItem::uMoved(const void *) {

    _obj->setPos(unit()->x(), unit()->y());

    QPointF bar_pos(unit()->x() - 1.2*unit()->size(), unit()->y() + 0.7*_obj->boundingRect().height());

    QPointF effect_im_pos = bar_pos;
    for(auto p : _effect_itens) {

        p.second->setPos(effect_im_pos);
        effect_im_pos.setX(effect_im_pos.x() + 15);
    }

    if(!_effect_itens.empty()) bar_pos.setY(bar_pos.y() + 20);

    ProgressBarItem *bars[] = { _health_bar, _energy_bar, _special_bar, _rage_bar };

    for(ProgressBarItem *bar : bars) {

        if(bar) {

            bar->setPos(bar_pos);
            bar_pos.setY(bar_pos.y() + 10);
        }
    }
}

void BasicUnitGraphicItem::uRotated(const void *) {

    _obj->setRotation(unit()->angle()*180/M_PI);
}

void BasicUnitGraphicItem::selectEffect() {

    _select_effect->setEnabled(true);
}

void BasicUnitGraphicItem::removeSelectEffect() {

    _select_effect->setEnabled(false);
}

void BasicUnitGraphicItem::uSkillStarted(const void *) {

    _obj->selectAnimation(unit()->skillId() + 1);
}

void BasicUnitGraphicItem::uSkillFinished(const void *) {

    _obj->selectAnimation(_obj->idleAnimation());
}

void BasicUnitGraphicItem::uSkillAdvance(const void *) {

    _obj->step();
    _update_effects();
}

void BasicUnitGraphicItem::uHealthChanged(const void *) {

    _health_bar->setValue(100*unit()->health()/unit()->maxHealth());
}

void BasicUnitGraphicItem::uEnergyConsumed(const void *) {

    if(_energy_bar) _energy_bar->setValue(100*unit()->energy()/unit()->maxEnergy());
}

void BasicUnitGraphicItem::uSpecialChanged(const void *) {

    if(_special_bar) _special_bar->setValue(100*unit()->special()/unit()->maxSpecial());
}

void BasicUnitGraphicItem::uRageChanged(const void *) {

    if(_rage_bar) _rage_bar->setValue(100*unit()->rage()/unit()->maxRage());
}

void BasicUnitGraphicItem::uEffectRemoved(const void *eff) {

    const UnitEffect *effect = reinterpret_cast<const UnitEffect *>(eff);

    auto it = _effect_itens.find(effect);

    if(it == _effect_itens.end()) return;

    delete it->second;

    _effect_itens.erase(it);

    uMoved(nullptr);
}

void BasicUnitGraphicItem::showAnimation() {

    _obj->show();
    _health_bar->show();
    if(_energy_bar) _energy_bar->show();

    for(auto p : _effect_itens) p.second->show();
}

void BasicUnitGraphicItem::hideAnimation() {

    _obj->hide();
    _health_bar->hide();
    if(_energy_bar) _energy_bar->hide();

    for(auto p : _effect_itens) p.second->hide();
}

void BasicUnitGraphicItem::_add_animations(const Animation& a) {

    _obj->addAnimation(a);
}

void BasicUnitGraphicItem::_update_effects() {

    Unit::EffectsList l = unit()->effects();

    for(auto p : l) {

        const UnitEffect *effect = p.first;
        const Unit::EffectInfo& info = p.second;

        if(info.renew) continue;

        auto it = _effect_itens.find(effect);

        if(it == _effect_itens.end()) continue;

        it->second->setValue(100*info.duration/info.starting_duration);
    }
}

void BasicUnitGraphicItem::_add_effect_item(const UnitEffect *effect) {

    if(_effect_itens.find(effect) != _effect_itens.end()) return;

    auto ei_it = _effect_images.find(typeid(*effect));

    if(ei_it == _effect_images.end()) ei_it = _effect_images.find(typeid(void));

    auto *item = new PartialImageItem(ei_it->second);
    _effect_itens[effect] = item;

    uMoved(nullptr);

    if(scene()) scene()->addItem(item);
}

void BasicUnitGraphicItem::_init() {

    QImage green_circle = QImage(":/green_circle.png").scaled(10, 10);
    _effect_images[typeid(void)] = green_circle;
    _effect_images[typeid(effect::Regeneration)] = QImage(":/red_cross.png").scaled(10, 12);
    _effect_images[typeid(effect::MagicShield)] = QImage(":/magic_shield.png").scaled(13, 13);

    utility::ImageColorChange green_to_black;

    green_to_black.addChInterval({0, 50}, {150, 255}, {0,50}, Qt::black);

    QImage black_circle = green_circle;
    green_to_black.changeImage(black_circle);

    _effect_images[typeid(effect::LastEscape)] = black_circle;

    utility::ImageColorChange green_to_red;

    green_to_red.addChInterval({0, 50}, {150, 255}, {0, 50}, Qt::red);

    QImage red_circle = green_circle;
    green_to_red.changeImage(red_circle);

    _effect_images[typeid(effect::Adrenaline)] = red_circle;

    _effect_images[typeid(effect::Shield)] = QImage(":/shield_icon.png").scaled(13, 13);
}

void BasicUnitGraphicItem::_init_bar(ProgressBarItem *bar, QColor color, UIntegerType width,
                                     UIntegerType height, UIntegerType value) {

    bar->setWidth(width);
    bar->setHeight(height);
    bar->setFgColor(color);
    bar->setValue(value);
}
