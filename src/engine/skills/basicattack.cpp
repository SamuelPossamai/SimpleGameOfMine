
#include "map.h"
#include "unit.h"
#include "skills/basicattack.h"

using namespace skill;

OneCopyMemoryManager<BasicAttack> BasicAttack::_skills;

UIntegerType BasicAttack::action(Unit *, Map *, const Info& info) {

    (void) info;


    return 1;
}
