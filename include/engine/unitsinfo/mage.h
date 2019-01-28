
#ifndef UNITSINFO_MAGE_H
#define UNITSINFO_MAGE_H

#include <memory/genericmemorymanager.h>

#include "unitinfo.h"

namespace unitsinfo {

class Mage : public UnitInfo, public GenericMemoryManager::ManagedObject {

    Mage() = default;

public:

    static Mage *getInfo() { return static_cast<Mage *>(getObjCopy(Mage())); }

    virtual ~Mage() override = default;

    virtual Skills getSkills(const Unit *) const override;

protected:

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType level) const override {

        return HealthType(100 + 6*attr.vitality() + level/2);
    }
    virtual EnergyType energyCalculate(const Attributes& attr, UIntegerType level) const override {

        return EnergyType(200 + 12*attr.wisdom() + level);
    }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override {

        return AttackType(2 + 0.2*attr.strength());
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return AccuracyType(15 + 0.7*attr.dexterity());
    }
    virtual MagicPowerType magicPowerCalculate(const Attributes& attr, UIntegerType) const override {

        return MagicPowerType(10 + attr.wisdom());
    }
    virtual MagicControlType magicControlCalculate(const Attributes& attr, UIntegerType) const override {

        return MagicControlType(5 + 1.5*attr.wisdom() + 0.2*attr.dexterity());
    }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType) const override {

        return SpeedType(55 + 0.55*attr.agility() + 0.2*attr.dexterity());
    }
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 24; }

    virtual GenericMemoryManager::ManagedObject *manObjClone() const override { return new Mage; }
};

} /* namespace unitsinfo */

#endif // UNITSINFO_MAGE_H
