#ifndef UNITINFO_H
#define UNITINFO_H

#include "traits.h"

class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

};

#endif // UNITINFO_H
