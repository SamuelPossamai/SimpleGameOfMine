#ifndef TESTSKILL_H
#define TESTSKILL_H

#include <unitskill.h>

namespace Skill {

class TestSkill : public UnitSkill {

    virtual UIntegerType action(Unit*, Map*, UIntegerType) override { return 0; }

    virtual UnitSkill *clone() override { return new TestSkill; }
};

} /* namespace Skills */

#endif // TESTSKILL_H
