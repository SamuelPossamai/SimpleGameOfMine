
#include "animation.h"
#include "animationfactories/unit/ninjaanimationfactory.h"
#include "animationitens/unit/basicunitgraphicitem.h"

using namespace unitanimationfactory;

NinjaAnimationFactory *NinjaAnimationFactory::_factory = nullptr;

NinjaAnimationFactory::NinjaAnimationFactory() :
    _walking_animation(20, true), _idle_animation(1000, true), _attacking_animation(80, false) {


    QPixmap walk_im1 = QPixmap(":/ninja_walking_1n3.png").scaledToWidth(70);
    QPixmap walk_im2 = QPixmap(":/ninja_walking_2.png").scaledToWidth(70);
    QPixmap walk_im3 = walk_im1;
    QPixmap walk_im4 = QPixmap(":/ninja_walking_4.png").scaledToWidth(70);
    QPixmap walk_im5 = QPixmap(":/ninja_walking_5.png").scaledToWidth(70);

    QPixmap attack_im1 = QPixmap(":/ninja_attack_1.png").scaledToWidth(80);
    QPixmap attack_im2 = QPixmap(":/ninja_attack_2.png").scaledToWidth(100);
    QPixmap attack_im3 = QPixmap(":/ninja_attack_3.png").scaledToWidth(100);

    _walking_animation.addImage(walk_im1, 0);
    _walking_animation.addImage(walk_im2, 4);
    _walking_animation.addImage(walk_im3, 8);
    _walking_animation.addImage(walk_im4, 12);
    _walking_animation.addImage(walk_im5, 16);

    _attacking_animation.addImage(attack_im1, 0);
    _attacking_animation.addImage(attack_im2, 10);
    _attacking_animation.addImage(attack_im3, 20);
    _attacking_animation.addImage(attack_im2, 30);

    _idle_animation.addImage(QPixmap(":/ninja_idle.png").scaledToWidth(70), 0);
}

UnitAnimationItem *NinjaAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(_idle_animation, _walking_animation, _attacking_animation,
                        _idle_animation, _idle_animation, _idle_animation);

    return item;
}

NinjaAnimationFactory *NinjaAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new NinjaAnimationFactory;

    return _factory;
}
