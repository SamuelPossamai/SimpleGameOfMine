
#include "animation.h"
#include "unitanimationfactories/slimeanimationfactory.h"
#include "unitanimations/basicunitgraphicitem.h"

namespace unitanimationfactory {

Animation SlimeAnimationFactory::_slime_animation(1000, true);
Animation SlimeAnimationFactory::_slime_attack_animation(10, true);
SlimeAnimationFactory *SlimeAnimationFactory::_factory = nullptr;

UnitAnimationItem *SlimeAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItem(u);

    item->setAnimations(_slime_animation, _slime_animation, _slime_animation, _slime_attack_animation);

    return item;
}

SlimeAnimationFactory *SlimeAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new SlimeAnimationFactory;

    _slime_animation.setFlag(Animation::Flag::RandomStart);

    QPixmap slime_im1 = QPixmap(":/slime_idle1.png").scaled(50, 50);
    QPixmap slime_im2 = QPixmap(":/slime_idle2.png").scaled(50, 50);
    QPixmap slime_im3 = QPixmap(":/slime_idle3.png").scaled(50, 50);
    QPixmap slime_im4 = QPixmap(":/slime_idle4.png").scaled(50, 50);
    QPixmap slime_im5 = QPixmap(":/slime_idle5.png").scaled(50, 50);

    _slime_animation.addImage(slime_im1, 0);
    _slime_animation.addImage(slime_im2, 200);
    _slime_animation.addImage(slime_im3, 400);
    _slime_animation.addImage(slime_im4, 600);
    _slime_animation.addImage(slime_im5, 800);

    _slime_attack_animation.addImage(QPixmap(":/slime_attack.png").scaled(150, 50), 0);

    return _factory;
}

} /* namespace unitanimationfactory */
