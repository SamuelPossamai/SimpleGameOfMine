
#ifndef SKILLS_MAGEONOFFMAGICSHIELD_H
#define SKILLS_MAGEONOFFMAGICSHIELD_H

#include "effects/magicshield.h"
#include "unitsinfo/unitclassinfo.h"
#include "unitskill.h"

namespace skill {

class MageOnOffMagicShield : public UnitSkill {

protected:

    MageOnOffMagicShield() : UnitSkill(false) {}

public:

    virtual UIntegerType action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info&) override;

    static MageOnOffMagicShield *getSkill() {

        if(!_skill) _skill =  new MageOnOffMagicShield;

        return _skill;
    }

private:

    static MageOnOffMagicShield *_skill;
};

} /* namespace skill */

#endif // SKILLS_MAGEONOFFMAGICSHIELD_H
