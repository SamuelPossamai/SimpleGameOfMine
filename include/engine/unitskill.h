
#ifndef UNITSKILL_H
#define UNITSKILL_H

#include <QPixmap>

#include "animation.h"

class UnitSkill {

public:

    struct Info {

        UIntegerType step;
        RealType angle;
    };

    virtual UIntegerType action(Unit *unit, Map *map, const Info& info) = 0;

    UIntegerType operator() (Unit *unit, Map *map, const Info& info) { return this->action(unit, map, info); }

    virtual UnitSkill *clone() const = 0;
};

#endif // UNITSKILL_H
