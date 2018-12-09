
#ifndef SKILLS_BASICATTACK_H
#define SKILLS_BASICATTACK_H

#include <memory/onecopymemorymanager.h>

#include "unitskill.h"

namespace skill {

class BasicAttack : public UnitSkill {

    friend class OneCopyMemoryManager<BasicAttack>;

protected:

    BasicAttack(UIntegerType distance, bool attack_from_above) : UnitSkill(true), _distance(distance),
        _att_from_above(attack_from_above) {}
    BasicAttack(const BasicAttack& other) : UnitSkill(true), _distance(other._distance), _att_from_above(other._att_from_above) {}

public:

    class MemoryInterface;

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    bool operator<(const BasicAttack& other) const {

        if(_distance != other._distance) return _distance < other._distance;
        return _att_from_above < other._att_from_above;
    }

    template<typename... Args>
    static BasicAttack *getSkill(Args... args) { return _skills.get(args...); }

private:

    UIntegerType _distance;
    bool _att_from_above;

    static OneCopyMemoryManager<BasicAttack> _skills;
};

class BasicAttack::MemoryInterface {

public:

    template <typename... Args>
    static BasicAttack *get(Args... args) { return BasicAttack::_skills.get(BasicAttack(args...)); }

    template <typename... Args>
    static BasicAttack *dependentGet(Args... args) { return BasicAttack::_skills.dependentGet(BasicAttack(args...)); }

    template <typename... Args>
    static void noLongerDepend(Args... args) { BasicAttack::_skills.noLongerDepend(BasicAttack(args...)); }
};

} /* namespace skill */

#endif // SKILLS_BASICATTACK_H
