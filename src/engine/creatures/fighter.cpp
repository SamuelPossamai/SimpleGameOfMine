
#include "animation.h"
#include "creatures/fighter.h"
#include "skills/walk.h"

namespace creature {

static UnitInfo *__fighter_info__ = nullptr;

static void __fighter_init__();

UnitInfo *fighterInfo() {

    if(__fighter_info__ == nullptr) __fighter_init__();

    return __fighter_info__;
}

void __fighter_init__() {

    __fighter_info__ = new UnitInfo;

    UnitInfo & __fighter_info__ = *creature::__fighter_info__;

    QPixmap walk_im1 = QPixmap(":/fighter_walking_1n3.png").scaledToWidth(70);
    QPixmap walk_im2 = QPixmap(":/fighter_walking_2.png").scaledToWidth(70);
    QPixmap walk_im3 = walk_im1;
    QPixmap walk_im4 = QPixmap(":/fighter_walking_4.png").scaledToWidth(70);
    QPixmap walk_im5 = QPixmap(":/fighter_walking_5.png").scaledToWidth(70);

    QPixmap attack_im1 = QPixmap(":/fighter_attack_1.png").scaledToWidth(80);
    QPixmap attack_im2 = QPixmap(":/fighter_attack_2.png").scaledToWidth(100);
    QPixmap attack_im3 = QPixmap(":/fighter_attack_3.png").scaledToWidth(100);

    Animation walking_animation(20, true);

    walking_animation.addImage(walk_im1, 0);
    walking_animation.addImage(walk_im2, 4);
    walking_animation.addImage(walk_im3, 8);
    walking_animation.addImage(walk_im4, 12);
    walking_animation.addImage(walk_im5, 16);

    Animation attacking_animation(80, false);

    attacking_animation.addImage(attack_im1, 0);
    attacking_animation.addImage(attack_im2, 20);
    attacking_animation.addImage(attack_im3, 40);
    attacking_animation.addImage(attack_im2, 60);

    Animation idle_animation(1000, true);

    idle_animation.addImage(QPixmap(":/fighter_idle.png").scaledToWidth(70), 0);

    __fighter_info__.addSkill(new skill::Walk(10, 140), walking_animation, QPixmap(":/wing_boot.png").scaled(50, 50));
    __fighter_info__.addSkill(new skill::Walk(60, 0), attacking_animation, QPixmap(":/x_simbol.png").scaled(50, 50));
    __fighter_info__.setIdleAnimation(idle_animation);

    __fighter_info__.setSize(20);
    __fighter_info__.setHealth(20);
}

} /* namespace creature */
