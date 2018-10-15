
#include "animation.h"
#include "animationfactories/unit/mageanimationfactory.h"
#include "animationitens/unit/basicunitgraphicitem.h"

using namespace unitanimationfactory;

MageAnimationFactory *MageAnimationFactory::_factory = nullptr;

MageAnimationFactory::MageAnimationFactory() :
    _walking_animation(25, true), _idle_animation(1000, true) {


    QPixmap walk_im1 = QPixmap(":/mage_walking_1n3.png").scaledToWidth(70);
    QPixmap walk_im2 = QPixmap(":/mage_walking_2.png").scaledToWidth(70);
    QPixmap walk_im3 = walk_im1;
    QPixmap walk_im4 = QPixmap(":/mage_walking_4.png").scaledToWidth(70);
    QPixmap walk_im5 = QPixmap(":/mage_walking_5.png").scaledToWidth(70);

    _walking_animation.addImage(walk_im1, 0);
    _walking_animation.addImage(walk_im2, 5);
    _walking_animation.addImage(walk_im3, 10);
    _walking_animation.addImage(walk_im4, 15);
    _walking_animation.addImage(walk_im5, 20);

    _idle_animation.addImage(QPixmap(":/mage_idle.png").scaledToWidth(70), 0);
}

UnitAnimationItem *MageAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(_idle_animation, _walking_animation, _idle_animation, _idle_animation);

    return item;
}

MageAnimationFactory *MageAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new MageAnimationFactory;

    return _factory;
}
