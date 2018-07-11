
#ifndef UNITEFFECT_H
#define UNITEFFECT_H

#include "unit.h"

class UnitEffect {

public:

    using HealthType = Unit::HealthType;
    using AttackType = Unit::AttackType;

    virtual ~UnitEffect() {}

    virtual void doTurnEffect(Unit *u, UIntegerType duration_left) const { Q_UNUSED(u); Q_UNUSED(duration_left); }
    virtual AttackType doAttackEffect(Unit *att, Unit *def, AttackType a) const { Q_UNUSED(att); Q_UNUSED(def); return a; }
    virtual AttackType doDefenseEffect(Unit *def, Unit *att, AttackType a) const { Q_UNUSED(def); Q_UNUSED(att); return a; }
};

#endif // UNITEFFECT_H
