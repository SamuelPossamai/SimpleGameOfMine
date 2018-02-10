
#ifndef SKILLS_EVADE_H
#define SKILLS_EVADE_H

#include "unitskill.h"

namespace skill {

class Evade : public UnitSkill {

public:

    Evade() : UnitSkill(false) {}

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    virtual UnitSkill *clone() const override { return new Evade; }
};

} /* namespace skill */

#endif // SKILLS_EVADE_H
