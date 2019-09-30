
#ifndef SKILLS_BASICATTACK_H
#define SKILLS_BASICATTACK_H

#include <memory/onecopymemorymanager.h>

#include "types.h"
#include "unitskill.h"

namespace skill {

class BasicAttack : public UnitSkill {

    friend class OneCopyMemoryManager<BasicAttack>;

protected:

    BasicAttack(UIntegerType distance, bool attack_from_above) :
        UnitSkill(UnitSkill::InputType::angle),
        _att_from_above(attack_from_above), _distance(distance) {}
    BasicAttack(const BasicAttack& other) : UnitSkill(true), _att_from_above(other._att_from_above), _distance(other._distance) {}

public:

    class MemoryInterface;

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    bool operator<(const BasicAttack& other) const {

        if(_distance != other._distance) return _distance < other._distance;
        return _att_from_above < other._att_from_above;
    }

    static UnitSkill *create(const sutils::VariantDataInfo& m);

    virtual void destroy() override;

private:

    bool _att_from_above;
    UIntegerType _distance;

    static OneCopyMemoryManager<BasicAttack> _skills;
};

class BasicAttack::MemoryInterface {

public:

    template <typename... Args>
    static BasicAttack *dependentGet(Args... args) { return BasicAttack::_skills.dependentGet(BasicAttack(args...)); }

    template <typename... Args>
    static void noLongerDepend(Args... args) { BasicAttack::_skills.noLongerDepend(BasicAttack(args...)); }
};

} /* namespace skill */

#endif // SKILLS_BASICATTACK_H
