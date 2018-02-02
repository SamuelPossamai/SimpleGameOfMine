#ifndef SKILLS_TESTSKILL_H
#define SKILLS_TESTSKILL_H

#include "unitskill.h"

namespace skill {

class TestSkill : public UnitSkill {

    virtual UIntegerType action(Unit*, Map*, UIntegerType) override;

    virtual UnitSkill *clone() const override { return new TestSkill; }
};

} /* namespace skill */

#endif // TESTSKILL_H
