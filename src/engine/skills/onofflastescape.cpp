
#include <engine/unit.h>
#include <engine/effects/lastescape.h>

#include "skills/onofflastescape.h"

using namespace skill;

OnOffLastEscape *OnOffLastEscape::_skill = nullptr;

UIntegerType OnOffLastEscape::action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info&) {

    UnitEffect *effect = effect::LastEscape::getEffect();
    if(!u->removeEffect(effect)) u->addEffect(effect);

    return 0;
}
