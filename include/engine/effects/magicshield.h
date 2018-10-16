
#ifndef EFFECTS_MAGICSHIELD_H
#define EFFECTS_MAGICSHIELD_H

#include <memory/genericmemorymanager.h>

#include "unit.h"
#include "uniteffect.h"

namespace effect {

class MagicShield : public UnitEffect, public GenericMemoryManager::ManagedObject {

    MagicShield(AttackType maximum_defense) : _maximum(maximum_defense) {}

public:

    virtual AttackType doDefenseEffect(Unit *def, Unit *, AttackType a) const override {

        AttackType att_blocked;

        att_blocked = a;

        if(att_blocked > _maximum) att_blocked = _maximum;
        if(att_blocked > def->energy()) att_blocked = def->energy();

        def->consumeEnergy(att_blocked);

        return a - att_blocked;
    }

    static MagicShield *getEffect(AttackType maximum_defense) {

        return static_cast<MagicShield *>(getObjCopy(MagicShield(maximum_defense)));
    }

    bool manObjLessCompare(const GenericMemoryManager::ManagedObject *other_mo) const override {

        auto other = static_cast<const MagicShield *>(other_mo);

        return this->_maximum < other->_maximum;
    }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new MagicShield(_maximum); }

private:

    AttackType _maximum;
};

} /* namespace effect */

#endif // EFFECTS_MAGICSHIELD_H
