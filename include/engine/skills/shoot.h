
#ifndef SKILLS_SHOOT_H
#define SKILLS_SHOOT_H

#include "unitskill.h"

namespace skill {

class Shoot : public UnitSkill {

protected:

    Shoot() : UnitSkill(true) {}

public:

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    static Shoot *getSkill() {

        if(!_skill) _skill =  new Shoot;

        return _skill;
    }

private:

    static Shoot *_skill;
};

} /* namespace skill */

#endif // SKILLS_SHOOT_H
