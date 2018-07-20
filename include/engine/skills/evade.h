
#ifndef SKILLS_EVADE_H
#define SKILLS_EVADE_H

#include "unitskill.h"

namespace skill {

class Evade : public UnitSkill {

protected:

    Evade() : UnitSkill(false) {}

public:

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    static Evade *getSkill() {

        if(!_skill) _skill =  new Evade;

        return _skill;
    }

private:

    static Evade *_skill;
};

} /* namespace skill */

#endif // SKILLS_EVADE_H
