
#ifndef SKILLS_KNIGHTBLOCK_H
#define SKILLS_KNIGHTBLOCK_H

#include "unitskill.h"

namespace skill {

class KnightBlock : public UnitSkill {

protected:

    KnightBlock() : UnitSkill(true) {}

public:

    virtual UIntegerType action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info& info) override;

    static KnightBlock *getSkill() {

        if(!_skill) _skill =  new KnightBlock;

        return _skill;
    }

    static UnitSkill *create(const utility::VariantDataInfo&) { return getSkill(); }

    virtual void destroy() override {}

private:

    static KnightBlock *_skill;
};

} /* namespace skill */

#endif // SKILLS_KNIGHTBLOCK_H
