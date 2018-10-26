
#include "animationfactories/unit/zuanimationfactory.h"
#include "animationitens/unit/basicunitgraphicitem.h"

using namespace unitanimationfactory;

ZuAnimationFactory *ZuAnimationFactory::_factory = nullptr;

ZuAnimationFactory::ZuAnimationFactory() : _idle_animation(20, true), _walking_animation(20, true) {

    QPixmap im1 = QPixmap(":/zu_walking_1.png").scaledToWidth(180);
    QPixmap im2 = QPixmap(":/zu_walking_2.png").scaledToWidth(180);

    _idle_animation.addImage(im1, 0);

    _walking_animation.addImage(im1, 0);
    _walking_animation.addImage(im2, 10);
}

UnitAnimationItem *ZuAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(_idle_animation, _walking_animation, _walking_animation, _walking_animation);

    return item;
}
