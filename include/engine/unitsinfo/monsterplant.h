
#ifndef UNITSINFO_MONSTERPLANT_H
#define UNITSINFO_MONSTERPLANT_H

#include "unitinfo.h"

namespace unitsinfo {

class MonsterPlant : public UnitInfo {

    MonsterPlant() = default;

public:

    virtual ~MonsterPlant() override = default;

    static MonsterPlant *getInfo() {

        if(_info) return _info;

        _info = new MonsterPlant;

        return _info;
    }

    virtual Skills getSkills(const Unit *) const override;

protected:

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType level) const override {

        return 400 + 35*attr.vitality() + attr.strength() + 2*level;
    }
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override {

        return AttackType(15 + 1.1*attr.strength() + 0.1*attr.dexterity());
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return AccuracyType(5 + 0.3*attr.dexterity());
    }
    virtual MagicPowerType magicPowerCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual MagicControlType magicControlCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType) const override {

        return SpeedType(60 + attr.agility() + 0.1*attr.dexterity());
    }
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 30; }

private:

    static MonsterPlant *_info;
};

} /* namespace creature */

#endif // UNITSINFO_MONSTERPLANT_H
