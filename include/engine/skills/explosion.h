
#ifndef SKILLS_EXPLOSION_H
#define SKILLS_EXPLOSION_H

#include "unit.h"
#include "unitskill.h"

namespace skill {

class Explosion : public UnitSkill {

protected:

    Explosion() : UnitSkill(true) {}

public:

    virtual UIntegerType action(Unit *, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    static Explosion *getSkill() {

        if(!_skill) _skill =  new Explosion;

        return _skill;
    }

private:

    static Explosion *_skill;
};

} /* namespace skill */

#endif // SKILLS_EXPLOSION_H
