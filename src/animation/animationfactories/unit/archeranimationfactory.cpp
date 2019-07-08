
#include "animation.h"
#include "animationfactories/unit/archeranimationfactory.h"
#include "animationitens/unit/basicunitgraphicitemmapped.h"

using namespace unitanimationfactory;

ArcherAnimationFactory *ArcherAnimationFactory::_factory = nullptr;

ArcherAnimationFactory::ArcherAnimationFactory() :
    _walking_animation(20, true), _idle_animation(1000, true), _attacking_animation(80, false), _shoot_animation(50, false) {


    QPixmap walk_im1 = QPixmap(":/archer_walking_1n3.png").scaledToWidth(70);
    QPixmap walk_im2 = QPixmap(":/archer_walking_2.png").scaledToWidth(70);
    QPixmap walk_im3 = walk_im1;
    QPixmap walk_im4 = QPixmap(":/archer_walking_4.png").scaledToWidth(70);
    QPixmap walk_im5 = QPixmap(":/archer_walking_5.png").scaledToWidth(70);

    QPixmap attack_im1 = QPixmap(":/archer_attack_1.png").scaledToWidth(80);
    QPixmap attack_im2 = QPixmap(":/archer_attack_2.png").scaledToWidth(100);
    QPixmap attack_im3 = QPixmap(":/archer_attack_3.png").scaledToWidth(100);

    QPixmap shoot_im1 = QPixmap(":/archer_shoot_1.png").scaledToWidth(100);
    QPixmap shoot_im2 = QPixmap(":/archer_shoot_2.png").scaledToWidth(100);
    QPixmap shoot_im3 = QPixmap(":/archer_shoot_3.png").scaledToWidth(120);
    QPixmap shoot_im4 = QPixmap(":/archer_shoot_4.png").scaledToWidth(120);

    _walking_animation.addImage(walk_im1, 0);
    _walking_animation.addImage(walk_im2, 4);
    _walking_animation.addImage(walk_im3, 8);
    _walking_animation.addImage(walk_im4, 12);
    _walking_animation.addImage(walk_im5, 16);

    _attacking_animation.addImage(attack_im1, 0);
    _attacking_animation.addImage(attack_im2, 10);
    _attacking_animation.addImage(attack_im3, 20);
    _attacking_animation.addImage(attack_im2, 30);

    _shoot_animation.addImage(shoot_im1, 0);
    _shoot_animation.addImage(shoot_im2, 10);
    _shoot_animation.addImage(shoot_im3, 15);
    _shoot_animation.addImage(shoot_im4, 20);

    _idle_animation.addImage(QPixmap(":/archer_idle.png").scaledToWidth(70), 0);
}

UnitAnimationItem *ArcherAnimationFactory::create(Unit *u) {

    auto *item = new unitanimation::BasicUnitGraphicItemMapped(u);

    item->addAnimation(_idle_animation, "__idle__");
    item->addAnimation(_walking_animation, "walk");
    item->addAnimation(_attacking_animation, "basic attack");
    item->addAnimation(_shoot_animation, "shoot");

    return item;
}

ArcherAnimationFactory *ArcherAnimationFactory::getFactory() {

    if(_factory) return _factory;

    _factory = new ArcherAnimationFactory;

    return _factory;
}
