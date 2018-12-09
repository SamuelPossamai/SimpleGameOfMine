
#ifndef UNITSINFO_FIGHTER_H
#define UNITSINFO_FIGHTER_H

#include "unitinfo.h"

namespace unitsinfo {

class Fighter : public UnitInfo {

protected:

    Fighter();

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType level) const override {

        return 199 + 12*attr.vitality() + 0.25*attr.strength() + level;
    }
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override {

        return 20 + attr.strength() + 0.3*attr.dexterity() + 0.1*attr.wisdom();
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return 30 + attr.dexterity();
    }
    virtual MagicPowerType magicPowerCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual MagicControlType magicControlCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType) const override {

        return 55 + 0.75*attr.agility() + 0.25*attr.dexterity();
    }
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 25; }

public:

    virtual ~Fighter();

    static Fighter *getInfo() {

        if(_info) return _info;

        _info = new Fighter;

        return _info;
    }

private:

    static Fighter *_info;
};

} /* namespace unitsinfo */

#endif // UNITSINFO_FIGHTER_H
