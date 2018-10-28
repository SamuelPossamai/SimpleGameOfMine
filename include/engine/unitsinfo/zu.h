
#ifndef UNITSINFO_ZU_H
#define UNITSINFO_ZU_H

#include "unitinfo.h"

namespace unitsinfo {

class Zu : public UnitInfo {

    Zu();

    virtual ~Zu() override;

public:

    static Zu *getInfo() {

        if(_info) return _info;

        _info = new Zu;

        return _info;
    }

protected:

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType level) const override {

        return 80 + 5*attr.vitality() + level;
    }
    virtual EnergyType energyCalculate(const Attributes& attr, UIntegerType level) const override {

        return 80 + 5*attr.wisdom() + level;
    }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType level) const override {

        return 5 + attr.strength() + level/4;
    }
    virtual AccuracyType accuracyCalculate(const Attributes& attr, UIntegerType) const override {

        return 15 + attr.dexterity();
    }
    virtual MagicPowerType magicPowerCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual MagicControlType magicControlCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual SpeedType speedCalculate(const Attributes& attr, UIntegerType level) const override {

        return 60 + attr.agility() + level/4;
    }
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 18; }

private:

    static Zu *_info;
};

} /* namespace creature */

#endif // UNITSINFO_ZU_H
