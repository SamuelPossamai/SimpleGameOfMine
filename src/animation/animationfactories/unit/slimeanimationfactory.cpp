
#include "animation.h"
#include "animationfactories/unit/slimeanimationfactory.h"
#include "animationitens/unit/basicunitgraphicitem.h"

using namespace unitanimationfactory;

SlimeAnimationFactory *SlimeAnimationFactory::_factory = nullptr;

SlimeAnimationFactory::SlimeAnimationFactory() : slimeNormalAnimation(1000, true), slimeAttackAnimation(10, true) {

    slimeNormalAnimation.setFlag(Animation::Flag::RandomStart);

    QPixmap slime_im1 = QPixmap(":/slime_idle1.png").scaled(50, 50);
    QPixmap slime_im2 = QPixmap(":/slime_idle2.png").scaled(50, 50);
    QPixmap slime_im3 = QPixmap(":/slime_idle3.png").scaled(50, 50);
    QPixmap slime_im4 = QPixmap(":/slime_idle4.png").scaled(50, 50);
    QPixmap slime_im5 = QPixmap(":/slime_idle5.png").scaled(50, 50);

    slimeNormalAnimation.addImage(slime_im1, 0);
    slimeNormalAnimation.addImage(slime_im2, 200);
    slimeNormalAnimation.addImage(slime_im3, 400);
    slimeNormalAnimation.addImage(slime_im4, 600);
    slimeNormalAnimation.addImage(slime_im5, 800);

    slimeAttackAnimation.addImage(QPixmap(":/slime_attack.png").scaled(150, 50), 0);
}

UnitAnimationItem *SlimeAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(slimeNormalAnimation, slimeNormalAnimation, slimeNormalAnimation, slimeAttackAnimation);

    return item;
}

SlimeAnimationFactory *SlimeAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new SlimeAnimationFactory;

    return _factory;
}
