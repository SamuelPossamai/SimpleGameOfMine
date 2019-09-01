
#ifndef SKILLS_MAGICMISSILE_H
#define SKILLS_MAGICMISSILE_H

#include "unitskill.h"

namespace skill {

class MagicMissile : public UnitSkill {

protected:

    MagicMissile() : UnitSkill(true) {}

public:

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    static MagicMissile *getSkill() {

        if(!_skill) _skill =  new MagicMissile;

        return _skill;
    }

    static UnitSkill *create(const sutils::VariantDataInfo&) { return getSkill(); }

    virtual void destroy() override {}

private:

    static MagicMissile *_skill;
};

} /* namespace skill */

#endif // SKILLS_MAGICMISSILE_H
