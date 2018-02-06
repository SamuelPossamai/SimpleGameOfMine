
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

    UnitSkill(bool need_angle = true) : _need_angle(need_angle) {}

    virtual UIntegerType action(Unit *unit, Map *map, const Info& info) = 0;

    UIntegerType operator() (Unit *unit, Map *map, const Info& info) { return this->action(unit, map, info); }

    virtual UnitSkill *clone() const = 0;

    bool needAngle() const { return _need_angle; }

private:

    const bool _need_angle;
};

#endif // UNITSKILL_H
