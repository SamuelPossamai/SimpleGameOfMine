
#include "animation.h"
#include "animationfactories/projectile/shurikenanimationfactory.h"
#include "animationitens/projectile/basicprojectilegraphicitem.h"

using namespace projectileanimationfactory;

ShurikenAnimationFactory *ShurikenAnimationFactory::_factory = nullptr;

ShurikenAnimationFactory::ShurikenAnimationFactory() : shurikenAnimation(1000, true) {

    QPixmap arrow_im = QPixmap(":/shuriken_image.png").scaled(32, 32);

    shurikenAnimation.addImage(arrow_im, 0);
}

ProjectileAnimationItem *ShurikenAnimationFactory::create(Projectile *u) {

    auto *item = new projectileanimation::BasicProjectileGraphicItem(u);

    item->setAnimations(shurikenAnimation);

    return item;
}

ShurikenAnimationFactory *ShurikenAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new ShurikenAnimationFactory;

    return _factory;
}
