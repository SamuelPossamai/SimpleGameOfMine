#ifndef UNITINFO_H
#define UNITINFO_H

#include "traits.h"

class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    UnitInfo() {}

private:

    HealthType _max_health;
    AttackType _base_attack;
    DefenseType _base_defense;

};

#endif // UNITINFO_H
