#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include <traits.h>

class UnitController {

public:

    UnitSkill *choose(Unit *, Map *, BattleEngine *) = 0;
};

#endif // UNITCONTROLLER_H
