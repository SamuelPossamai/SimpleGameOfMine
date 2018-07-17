
#ifndef SKILLS_BASICATTACK_H
#define SKILLS_BASICATTACK_H

#include <utility/onecopymemorymanager.h>

#include "unitskill.h"

namespace skill {

class BasicAttack : public UnitSkill {

    friend class utility::OneCopyMemoryManager<BasicAttack>;

protected:

    BasicAttack(UIntegerType distance, UIntegerType damage) : UnitSkill(true), _distance(distance), _damage(damage) {}
    BasicAttack(const BasicAttack& other) : UnitSkill(true), _distance(other._distance), _damage(other._damage) {}

public:

    virtual UIntegerType action(Unit*, Map*, const Info&) override;

    bool operator<(const BasicAttack& other) const {

        if(_distance < other._distance) return true;
        if(_damage < other._damage) return true;
        return false;
    }

    template<typename... Args>
    static BasicAttack *getSkill(Args... args) { return _skills.get(args...); }

private:

    UIntegerType _distance;
    UIntegerType _damage;

    static utility::OneCopyMemoryManager<BasicAttack> _skills;
};

}

#endif // SKILLS_BASICATTACK_H
