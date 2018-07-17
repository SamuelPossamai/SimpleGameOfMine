
#ifndef SKILLS_WALK_H
#define SKILLS_WALK_H

#include <utility/onecopymemorymanager.h>

#include "unitskill.h"

namespace skill {

class Walk : public UnitSkill {

    friend class utility::OneCopyMemoryManager<Walk>;

protected:

    using MemoryManager = utility::OneCopyMemoryManager<Walk>;

    Walk(UIntegerType duration, UIntegerType distance) : Walk(true, duration, distance) {}
    Walk(const Walk& other) : Walk(true, other) {}
    Walk(bool need_arrow, UIntegerType duration, UIntegerType distance) : UnitSkill(need_arrow),
        _dur(duration), _ds(distance/duration) {}
    Walk(bool need_arrow, const Walk& other) : UnitSkill(need_arrow), _dur(other._dur), _ds(other._ds) {}

public:

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    bool operator<(const Walk& other) const {

        if(_dur < other._dur) return true;
        if(_ds < other._ds) return true;
        return false;
    }

    template<typename... Args>
    static Walk *getSkill(Args... args) { return _skills.get(args...); }

protected:

    UIntegerType doAction(Unit *, Map *, const Info&, RealType);

private:

    UIntegerType _dur;
    UIntegerType _ds;

    static MemoryManager _skills;
};

} /* namespace skill */

#endif // SKILLS_WALK_H
