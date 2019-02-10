
#ifndef SKILLS_WALK_H
#define SKILLS_WALK_H

#include <iostream>

#include <memory/onecopymemorymanager.h>

#include "unitskill.h"

namespace skill {

class Walk : public UnitSkill {

protected:

    using MemoryManager = OneCopyMemoryManager<Walk>;

    Walk(UIntegerType duration, UIntegerType distance) : Walk(true, duration, distance) {}
    Walk(const Walk& other) : Walk(true, other) {}
    Walk(bool need_arrow, UIntegerType duration, UIntegerType distance) : UnitSkill(need_arrow),
        _dur(duration), _ds(distance/duration) {}
    Walk(bool need_arrow, const Walk& other) : UnitSkill(need_arrow), _dur(other._dur), _ds(other._ds) {}

public:

    class MemoryInterface;

    virtual ~Walk() override = default;

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    bool operator<(const Walk& other) const {

        if(_dur != other._dur) return _dur < other._dur;

        return _ds < other._ds;
    }

    static UnitSkill *create(const utility::VariantDataInfo& m);

    virtual void destroy() override;

    static UIntegerType walk(Unit *, UIntegerType step, UIntegerType dur, UIntegerType ds, RealType angle);

protected:

    UIntegerType doAction(Unit *, EngineMap *, const Info&, RealType);

    static Walk fromVariantData(const utility::VariantDataInfo& m);

private:

    static Walk *_clone(const Walk& w) { return new Walk(w); }

    UIntegerType _dur;
    UIntegerType _ds;

    static MemoryManager _skills;
};

class Walk::MemoryInterface {

public:

    template <typename... Args>
    static Walk *get(Args... args) { return Walk::_skills.get(_create(args...)); }

    template <typename... Args>
    static Walk *dependentGet(Args... args) { return Walk::_skills.dependentGet(_create(args...)); }

    template <typename... Args>
    static void noLongerDepend(Args... args) { Walk::_skills.noLongerDepend(_create(args...)); }

private:

    static Walk _create(const Walk& w) { return Walk(w); }
    static Walk _create(UIntegerType duration, UIntegerType distance) { return Walk(duration, distance); }
};

} /* namespace skill */

#endif // SKILLS_WALK_H
