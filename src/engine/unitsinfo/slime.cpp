
#include "animation.h"
#include "unitsinfo/slime.h"
#include "skills/walk.h"
#include "skills/evade.h"
#include "skills/thrust.h"

namespace unitsinfo {

static UnitInfo *__slime_info__ = nullptr;

static void __slime_init__();

UnitInfo *slimeInfo() {

    if(__slime_info__ == nullptr) __slime_init__();

    return __slime_info__;
}

void __slime_init__() {

    __slime_info__ = new UnitInfo;

    UnitInfo & __slime_info__ = *unitsinfo::__slime_info__;

    QPixmap slime_im1 = QPixmap(":/slime_idle1.png").scaled(50, 50);
    QPixmap slime_im2 = QPixmap(":/slime_idle2.png").scaled(50, 50);
    QPixmap slime_im3 = QPixmap(":/slime_idle3.png").scaled(50, 50);
    QPixmap slime_im4 = QPixmap(":/slime_idle4.png").scaled(50, 50);
    QPixmap slime_im5 = QPixmap(":/slime_idle5.png").scaled(50, 50);

    Animation slime_animation(1000, true);

    slime_animation.setFlag(Animation::Flag::RandomStart);

    slime_animation.addImage(slime_im1, 0);
    slime_animation.addImage(slime_im2, 200);
    slime_animation.addImage(slime_im3, 400);
    slime_animation.addImage(slime_im4, 600);
    slime_animation.addImage(slime_im5, 800);

    Animation slime_attack_animation(10, true);

    slime_attack_animation.addImage(QPixmap(":/slime_attack.png").scaled(150, 50), 0);

    __slime_info__.addSkill(new skill::Walk(10, 100), slime_animation, QPixmap(":/wing_boot.png").scaled(50, 50));
    __slime_info__.addSkill(new skill::Evade, slime_animation, QPixmap(":/wing_boot_blue.png").scaled(50, 50));
    __slime_info__.addSkill(new skill::Thrust(12, 90), slime_attack_animation, QPixmap(":/x_simbol.png").scaled(50, 50));
    __slime_info__.setIdleAnimation(slime_animation);

    __slime_info__.setSize(22);
    __slime_info__.setHealth(10);
}

} /* namespace creature */
