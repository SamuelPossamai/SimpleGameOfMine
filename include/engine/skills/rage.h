
#ifndef SKILLS_RAGE_H
#define SKILLS_RAGE_H

#include "unitskill.h"

namespace skill {

class Rage : public UnitSkill {

protected:

    Rage() : UnitSkill(false) {}

public:

    virtual UIntegerType action(Unit *, EngineMap *, ProjectileCreationInterface&, const Info&) override;

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static Rage *getSkill() { if(!_skill) _skill = new Rage; return _skill; }

private:

    static Rage *_skill;
};

} /* namespace skill */

#endif // SKILLS_RAGE_H
