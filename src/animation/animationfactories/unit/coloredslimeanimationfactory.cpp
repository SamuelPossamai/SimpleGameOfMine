
#include <utility/imagecolorchange.h>

#include "animation.h"
#include "animationfactories/unit/coloredslimeanimationfactory.h"
#include "animationitens/unit/basicunitgraphicitem.h"

using namespace unitanimationfactory;

OneCopyMemoryManager<ColoredSlimeAnimationFactory> ColoredSlimeAnimationFactory::_memmanager;

ColoredSlimeAnimationFactory::ColoredSlimeAnimationFactory(QColor color) : _color(color) {

    utility::ImageColorChange icch;

    icch.addChInterval({0, 50}, {150, 256}, {0, 50}, color);
    slimeNormalAnimation.changeColor(icch);
    slimeAttackAnimation.changeColor(icch);
}

UnitAnimationItem *ColoredSlimeAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(slimeNormalAnimation, slimeNormalAnimation, slimeNormalAnimation, slimeAttackAnimation);

    return item;
}
