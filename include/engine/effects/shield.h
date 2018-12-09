
#ifndef EFFECTS_SHIELD_H
#define EFFECTS_SHIELD_H

#include <cmath>

#include "unit.h"
#include "enginemap.h"
#include "genericmemorymanager.h"
#include "uniteffect.h"

namespace effect {

class Shield : public UnitEffect, public GenericMemoryManager::ManagedObject {

    Shield(AttackType maximum_defense) : _def(maximum_defense) {}

public:

    virtual AttackType doDefenseEffect(Unit *def, EngineObject *att, AttackType a) const override {

        Unit::AngleType angle_diff =
                EngineMap::angleDiff(std::atan2(def->y() - att->y(), def->x() - att->x()), def->angle());

        constexpr static const Unit::AngleType maximum_angle = M_PI;

        if(angle_diff > maximum_angle) return a;

        AttackType defense_value = (angle_diff/maximum_angle)*_def;

        if(a > defense_value) return a - defense_value;

        return 0;
    }

    static Shield *getEffect(AttackType maximum_defense) {

        return static_cast<Shield *>(getObjCopy(Shield(maximum_defense)));
    }

    bool manObjLessCompare(const GenericMemoryManager::ManagedObject *other_mo) const override {

        auto other = static_cast<const Shield *>(other_mo);

        return this->_def < other->_def;
    }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Shield(_def); }

private:

    AttackType _def;
};

} /* namespace effect */

#endif // EFFECTS_SHIELD_H
