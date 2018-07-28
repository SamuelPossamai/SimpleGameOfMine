
#include <engine/skills/teleport.h>
#include <engine/unit.h>

#include "effects/lastescape.h"

using namespace effect;

LastEscape *LastEscape::_copy = nullptr;

LastEscape::AttackType LastEscape::doDefenseEffect(Unit *def, Unit *, AttackType a) const {

    if(def->consumeEnergy(10)) {

        skill::Teleport::teleportUnit(def);
        return 0;
    }

    return a;
}

