
#ifndef SKILLS_THRUST_H
#define SKILLS_THRUST_H

#include "unitskill.h"
#include "walk.h"

#include <memory/onecopymemorymanager.h>

namespace skill {

class Thrust : public Walk {

    friend class OneCopyMemoryManager<Thrust>;

protected:

    Thrust(UIntegerType duration, UIntegerType distance) : Walk(false, duration, distance) {}
    Thrust(const Thrust& other) : Walk(false, other) {}

public:

    class MemoryInterface;

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

private:

    static OneCopyMemoryManager<Thrust> _skills;
};

class Thrust::MemoryInterface {

public:

    template <typename... Args>
    static Thrust *get(Args... args) { return Thrust::_skills.get(Thrust(args...)); }

    template <typename... Args>
    static Thrust *dependentGet(Args... args) { return Thrust::_skills.dependentGet(Thrust(args...)); }

    template <typename... Args>
    static void noLongerDepend(Args... args) { Thrust::_skills.noLongerDepend(Thrust(args...)); }
};

} /* namespace skill */

#endif // SKILLS_THRUST_H
