
#include "unitanimations/basicunitgraphicitem.h"
#include "unitanimationfactories/monsterfloweranimationfactory.h"

using namespace unitanimationfactory;

MonsterFlowerAnimationFactory *MonsterFlowerAnimationFactory::_factory = nullptr;

MonsterFlowerAnimationFactory::MonsterFlowerAnimationFactory() :
    _idle_animation(20, true), _walking_animation(20, true), _attacking_animation(80, false) {

    QPixmap im1 = QPixmap(":/monsterplant_img1.png").scaledToWidth(300);
    QPixmap im2 = QPixmap(":/monsterplant_img2.png").scaledToWidth(300);

    _idle_animation.addImage(im2, 0);

    _walking_animation.addImage(im1, 0);
    _walking_animation.addImage(im2, 10);
}

UnitAnimationItem *MonsterFlowerAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(_idle_animation, _walking_animation, _walking_animation);

    return item;
}
