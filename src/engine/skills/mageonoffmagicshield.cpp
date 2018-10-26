
#include "skills/mageonoffmagicshield.h"

using namespace skill;

MageOnOffMagicShield *MageOnOffMagicShield::_skill = nullptr;

UIntegerType MageOnOffMagicShield::action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info&) {

    UnitEffect *effect = effect::MagicShield::getEffect(5 + u->attributes().wisdom()/4);
    if(!u->removeEffect(effect)) u->addEffect(effect);

    return 0;
}

