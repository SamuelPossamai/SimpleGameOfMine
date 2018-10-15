
#include "animation.h"
#include "animationfactories/projectile/magicmissilefactory.h"
#include "animationitens/projectile/basicprojectilegraphicitem.h"

using namespace projectileanimationfactory;

MagicMissileFactory *MagicMissileFactory::_factory = nullptr;

MagicMissileFactory::MagicMissileFactory() : missileAnimation(30, true) {

    QPixmap missile_im1 = QPixmap(":/magic_missile_1.png").scaled(40, 40);
    QPixmap missile_im2 = QPixmap(":/magic_missile_2.png").scaled(40, 40);
    QPixmap missile_im3 = QPixmap(":/magic_missile_3.png").scaled(40, 40);
    QPixmap missile_im4 = QPixmap(":/magic_missile_4.png").scaled(40, 40);

    missileAnimation.addImage(missile_im1, 0);
    missileAnimation.addImage(missile_im2, 5);
    missileAnimation.addImage(missile_im3, 10);
    missileAnimation.addImage(missile_im4, 15);
    missileAnimation.addImage(missile_im3, 20);
    missileAnimation.addImage(missile_im2, 25);
}

ProjectileAnimationItem *MagicMissileFactory::create(Projectile *u) {

    auto *item = new projectileanimation::BasicProjectileGraphicItem(u);

    item->setAnimations(missileAnimation);

    return item;
}

MagicMissileFactory *MagicMissileFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new MagicMissileFactory;

    return _factory;
}
