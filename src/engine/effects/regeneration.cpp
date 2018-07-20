
#include "effects/regeneration.h"

using namespace effect;

OneCopyMemoryManager<Regeneration, Regeneration::RegCompare> Regeneration::_effects(_clone);

