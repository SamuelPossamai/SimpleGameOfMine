#ifndef UNITINFO_H
#define UNITINFO_H

#include "traits.h"

class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;
    using SizeType = Traits<Unit>::SizeType;

    UnitInfo() {}

    void setHealth(HealthType health) { _max_health = health; }
    HealthType health() const { return _max_health; }

    void setBaseAttack(AttackType attack) { _base_attack = attack; }
    AttackType baseAttack() { return _base_attack; }

    void setSize(SizeType size) { _size = size; }
    SizeType size() const { return _size; }

private:

    HealthType _max_health;
    AttackType _base_attack;
    DefenseType _base_defense;

    SizeType _size;
};

#endif // UNITINFO_H
