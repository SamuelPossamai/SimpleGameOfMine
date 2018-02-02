
#include <iostream>

#include "skills/testskill.h"
#include "unit.h"

namespace skill {

UIntegerType TestSkill::action(Unit *u, Map*, UIntegerType s) {

    if(s < 20) {

        u->setX(u->x() + 2);
        u->setAngle(u->angle() + 0.01);

        return s + 1;
    }

    return 0;
}


} /* namespace skill */
