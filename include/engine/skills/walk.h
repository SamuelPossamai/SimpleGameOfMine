
#ifndef SKILLS_WALK_H
#define SKILLS_WALK_H

#include "unitskill.h"

namespace skill {

class Walk : public UnitSkill {

public:

    Walk(UIntegerType duration, UIntegerType distance) : Walk(true, duration, distance) {}
    Walk(const Walk& other) : Walk(true, other) {}

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    virtual UnitSkill *clone() const override { return new Walk(*this); }

protected:

    UIntegerType doAction(Unit *, Map *, const Info&, RealType);

    Walk(bool need_arrow, UIntegerType duration, UIntegerType distance) : UnitSkill(need_arrow),
        _dur(duration), _ds(distance/duration) {}

    Walk(bool need_arrow, const Walk& other) : UnitSkill(need_arrow), _dur(other._dur), _ds(other._ds) {}

private:

    UIntegerType _dur;
    UIntegerType _ds;
};

} /* namespace skill */

#endif // SKILLS_WALK_H
