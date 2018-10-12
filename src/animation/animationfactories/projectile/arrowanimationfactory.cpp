
#include "animation.h"
#include "animationfactories/projectile/arrowanimationfactory.h"
#include "animationitens/projectile/basicprojectilegraphicitem.h"

using namespace projectileanimationfactory;

ArrowAnimationFactory *ArrowAnimationFactory::_factory = nullptr;

ArrowAnimationFactory::ArrowAnimationFactory() : arrowAnimation(1000, true) {

    QPixmap arrow_im = QPixmap(":/arrow_projectile_image.png").scaled(40, 40);

    arrowAnimation.addImage(arrow_im, 0);
}

ProjectileAnimationItem *ArrowAnimationFactory::create(Projectile *u) {

    auto *item = new projectileanimation::BasicProjectileGraphicItem(u);

    item->setAnimations(arrowAnimation);

    return item;
}

ArrowAnimationFactory *ArrowAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new ArrowAnimationFactory;

    return _factory;
}
