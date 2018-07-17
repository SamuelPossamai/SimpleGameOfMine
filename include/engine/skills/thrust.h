
#ifndef SKILLS_THRUST_H
#define SKILLS_THRUST_H

#include "unitskill.h"
#include "walk.h"

#include <utility/onecopymemorymanager.h>

namespace skill {

class Thrust : public Walk {

    friend class utility::OneCopyMemoryManager<Thrust>;

protected:

    Thrust(UIntegerType duration, UIntegerType distance) : Walk(false, duration, distance) {}
    Thrust(const Thrust& other) : Walk(false, other) {}

public:

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    template <typename... Args>
    static Thrust *getSkill(Args... args) { return _skills.get(args...); }

private:

    static utility::OneCopyMemoryManager<Thrust> _skills;
};

} /* namespace skill */

#endif // SKILLS_THRUST_H
