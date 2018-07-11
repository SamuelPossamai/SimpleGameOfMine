
#include <utility/imagecolorchange.h>

#include "animation.h"
#include "unitanimationfactories/redslimeanimationfactory.h"
#include "unitanimations/basicunitgraphicitem.h"

using namespace unitanimationfactory;

RedSlimeAnimationFactory *RedSlimeAnimationFactory::_factory = nullptr;

RedSlimeAnimationFactory::RedSlimeAnimationFactory() {

    utility::ImageColorChange icch;

    icch.addChInterval({0, 50}, {150, 256}, {0, 50}, Qt::red);
    slimeNormalAnimation.changeColor(icch);
    slimeAttackAnimation.changeColor(icch);
}

UnitAnimationItem *RedSlimeAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(slimeNormalAnimation, slimeNormalAnimation, slimeNormalAnimation, slimeAttackAnimation);

    return item;
}

RedSlimeAnimationFactory *RedSlimeAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new RedSlimeAnimationFactory;

    return _factory;
}
