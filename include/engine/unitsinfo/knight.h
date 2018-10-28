
#ifndef UNITSINFO_KNIGHT_H
#define UNITSINFO_KNIGHT_H

#include "unitinfo.h"

namespace unitsinfo {

class Knight : public UnitInfo {

protected:

    Knight();

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType level) const override {

        return 300 + 20*attr.vitality() + 0.1*attr.strength() + level;
    }
    virtual EnergyType energyCalculate(const Attributes& attr, UIntegerType level) const override {

        return 10 + attr.wisdom() + attr.vitality() + level/4;
    }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override {

        return 16 + 0.85*attr.strength() + 0.1*attr.dexterity() + 0.2*attr.wisdom();
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return 25 + 0.8*attr.dexterity();
    }
    virtual MagicPowerType magicPowerCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual MagicControlType magicControlCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType) const override;
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 28; }

public:

    virtual ~Knight();

    static Knight *getInfo() {

        if(_info) return _info;

        _info = new Knight;

        return _info;
    }

private:

    static Knight *_info;
};

} /* namespace unitsinfo */

#endif // UNITSINFO_KNIGHT_H
