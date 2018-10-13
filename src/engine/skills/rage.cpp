
#include <engine/unit.h>
#include <engine/effects/adrenaline.h>

#include "skills/rage.h"

using namespace skill;

Rage *Rage::_skill = nullptr;

UIntegerType Rage::action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info& i) {

    if(i.step >= 10) return 0;

    if(!u->consumeEnergy(5)) return 0;

    UnitEffect *effect = effect::Adrenaline::getEffect();
    u->removeEffect(effect);
    u->addEffect(effect, 300);

    return 10;
}
