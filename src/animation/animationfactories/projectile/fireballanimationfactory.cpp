
#include "animation.h"
#include "animationfactories/projectile/fireballanimationfactory.h"
#include "animationitens/projectile/basicprojectilegraphicitem.h"

using namespace projectileanimationfactory;

FireballAnimationFactory *FireballAnimationFactory::_factory = nullptr;

FireballAnimationFactory::FireballAnimationFactory() : fireballAnimation(1000, true) {

    QPixmap arrow_im = QPixmap(":/fireball_image.png").scaled(40, 25);

    fireballAnimation.addImage(arrow_im, 0);
}

ProjectileAnimationItem *FireballAnimationFactory::create(Projectile *u) {

    auto *item = new projectileanimation::BasicProjectileGraphicItem(u);

    item->setAnimations(fireballAnimation);

    return item;
}

FireballAnimationFactory *FireballAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new FireballAnimationFactory;

    return _factory;
}
