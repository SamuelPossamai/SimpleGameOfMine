
#include "skills/mageonoffmagicshield.h"

using namespace skill;

MageOnOffMagicShield *MageOnOffMagicShield::_skill = nullptr;

UIntegerType MageOnOffMagicShield::action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info&) {

    auto u_info = static_cast<const unitsinfo::UnitClassInfo *>(u->unitInfo());

    UnitEffect *effect = effect::MagicShield::getEffect(5 + u_info->attributes().wisdom()/4);
    if(!u->removeEffect(effect)) u->addEffect(effect);

    return 0;
}

