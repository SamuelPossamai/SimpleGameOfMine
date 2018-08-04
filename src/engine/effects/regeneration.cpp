
#include <engine/unit.h>

#include "effects/regeneration.h"

using namespace effect;

OneCopyMemoryManager<Regeneration, Regeneration::RegCompare> Regeneration::_effects(_clone);

void Regeneration::doTurnEffect(Unit *u, UIntegerType duration_left) const {

    if(!(duration_left%_period)) u->heal(u, _amount);
}
