
#ifndef UNITSKILL_H
#define UNITSKILL_H

#include <QPixmap>

#include "animation.h"

class UnitSkill {

public:

    virtual UIntegerType action(Unit *unit, Map *map, UIntegerType step) = 0;

    UIntegerType operator() (Unit *unit, Map *map, UIntegerType step) { return this->action(unit, map, step); }

    virtual UnitSkill *clone() const = 0;
};

#endif // UNITSKILL_H
