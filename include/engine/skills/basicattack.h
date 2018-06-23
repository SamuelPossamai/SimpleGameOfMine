
#ifndef SKILLS_BASICATTACK_H
#define SKILLS_BASICATTACK_H

#include "unitskill.h"

namespace skill {

class BasicAttack : public UnitSkill {

public:

    BasicAttack(UIntegerType distance, UIntegerType damage) : UnitSkill(true), _distance(distance), _damage(damage) {}
    BasicAttack(const BasicAttack& other) : UnitSkill(true), _distance(other._distance), _damage(other._damage) {}

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    virtual UnitSkill *clone() const override { return new BasicAttack(*this); }

private:

    UIntegerType _distance;
    UIntegerType _damage;
};

}

#endif // SKILLS_BASICATTACK_H
