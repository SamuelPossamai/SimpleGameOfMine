
#include "animation.h"
#include "unitanimationfactories/fighteranimationfactory.h"
#include "unitanimations/basicunitgraphicitem.h"

namespace unitanimationfactory {

Animation FighterAnimationFactory::_walking_animation(20, true);
Animation FighterAnimationFactory::_idle_animation(1000, true);
Animation FighterAnimationFactory::_attacking_animation(80, false);

FighterAnimationFactory *FighterAnimationFactory::_factory = nullptr;

UnitAnimationItem *FighterAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(_idle_animation, _walking_animation, _attacking_animation);

    return item;
}

FighterAnimationFactory *FighterAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new FighterAnimationFactory;

    QPixmap walk_im1 = QPixmap(":/fighter_walking_1n3.png").scaledToWidth(70);
    QPixmap walk_im2 = QPixmap(":/fighter_walking_2.png").scaledToWidth(70);
    QPixmap walk_im3 = walk_im1;
    QPixmap walk_im4 = QPixmap(":/fighter_walking_4.png").scaledToWidth(70);
    QPixmap walk_im5 = QPixmap(":/fighter_walking_5.png").scaledToWidth(70);

    QPixmap attack_im1 = QPixmap(":/fighter_attack_1.png").scaledToWidth(80);
    QPixmap attack_im2 = QPixmap(":/fighter_attack_2.png").scaledToWidth(100);
    QPixmap attack_im3 = QPixmap(":/fighter_attack_3.png").scaledToWidth(100);

    _walking_animation.addImage(walk_im1, 0);
    _walking_animation.addImage(walk_im2, 4);
    _walking_animation.addImage(walk_im3, 8);
    _walking_animation.addImage(walk_im4, 12);
    _walking_animation.addImage(walk_im5, 16);

    _attacking_animation.addImage(attack_im1, 0);
    _attacking_animation.addImage(attack_im2, 20);
    _attacking_animation.addImage(attack_im3, 40);
    _attacking_animation.addImage(attack_im2, 60);

    _idle_animation.addImage(QPixmap(":/fighter_idle.png").scaledToWidth(70), 0);

    return _factory;
}

} /* namespace unitanimationfactory */
