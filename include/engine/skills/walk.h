
#ifndef WALK_H
#define WALK_H

#include "unitskill.h"

namespace skill {

class Walk : public UnitSkill {

public:

    Walk(UIntegerType duration, UIntegerType distance) : _dur(duration), _ds(distance/duration) {}

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    virtual UnitSkill *clone() const override { auto *ptr = new Walk(_dur, 0); ptr->_ds = _ds; return ptr; }

private:

    UIntegerType _dur;
    UIntegerType _ds;
};

} /* namespace skill */

#endif // WALK_H
