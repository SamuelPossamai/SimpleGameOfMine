
#include "skills/mageonoffmagicshield.h"

using namespace skill;

MageOnOffMagicShield *MageOnOffMagicShield::_skill = nullptr;

UIntegerType MageOnOffMagicShield::action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info&) {

    UnitEffect *effect = effect::MagicShield::getEffect(u->magicPower()/3);
    if(!u->removeEffect(effect)) u->addEffect(effect);

    return 0;
}

