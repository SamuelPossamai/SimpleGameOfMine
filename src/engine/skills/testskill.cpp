
#include <iostream>

#include "skills/testskill.h"
#include "unit.h"

namespace skill {

UIntegerType TestSkill::action(Unit *u, Map*, const Info& info) {

    if(info.step < 20) {

        u->setX(u->x() + 2);
        u->setAngle(u->angle() + 0.01);

        return 1;
    }

    return 0;
}

UIntegerType TestSkill_2::action(Unit *u, Map*, const Info& info) {

    if(info.step < 200) {

        u->setX(u->x() + 1);

        return 10;
    }

    return 0;
}

} /* namespace skill */
