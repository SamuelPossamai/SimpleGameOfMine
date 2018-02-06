#ifndef SKILLS_TESTSKILL_H
#define SKILLS_TESTSKILL_H

#include "unitskill.h"

namespace skill {

class TestSkill : public UnitSkill {

public:

    TestSkill() : UnitSkill(false) {}

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    virtual UnitSkill *clone() const override { return new TestSkill; }
};

class TestSkill_2 : public UnitSkill {

public:

    TestSkill_2() : UnitSkill(false) {}

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    virtual UnitSkill *clone() const override { return new TestSkill_2; }
};

} /* namespace skill */

#endif // TESTSKILL_H
