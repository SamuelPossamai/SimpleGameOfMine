
#ifndef SKILLS_FIREBALL_H
#define SKILLS_FIREBALL_H

#include "unit.h"
#include "unitskill.h"

namespace skill {

class Fireball : public UnitSkill {

protected:

    Fireball() : UnitSkill(true) {}

public:

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    static Fireball *getSkill() {

        if(!_skill) _skill =  new Fireball;

        return _skill;
    }

    static void shoot(Unit *, ProjectileCreationInterface&, Unit::AngleType angle);

    static UnitSkill *create(const utility::VariantDataInfo&) { return getSkill(); }

    virtual void destroy() override {}

private:

    static Fireball *_skill;
};

} /* namespace skill */

#endif // SKILLS_FIREBALL_H
