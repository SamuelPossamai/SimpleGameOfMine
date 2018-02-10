
#ifndef SKILLS_THRUST_H
#define SKILLS_THRUST_H

#include "unitskill.h"
#include "walk.h"

namespace skill {

class Thrust : public Walk {

public:

    Thrust(UIntegerType duration, UIntegerType distance) : Walk(false, duration, distance) {}
    Thrust(const Thrust& other) : Walk(false, other) {}

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    virtual UnitSkill *clone() const override { return new Thrust(*this); }
};

} /* namespace skill */

#endif // SKILLS_THRUST_H
