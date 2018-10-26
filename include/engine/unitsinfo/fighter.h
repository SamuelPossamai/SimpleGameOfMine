
#ifndef UNITSINFO_FIGHTER_H
#define UNITSINFO_FIGHTER_H

#include <memory/onecopymemorymanager.h>

#include "unitinfo.h"

namespace unitsinfo {

class Fighter : public UnitInfo {

protected:

    Fighter();

    virtual HealthType healthCalculate(const Attributes& attr, UIntegerType) const override {

        return 200 + 12*attr.vitality() + 0.25*attr.strength();
    }
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual AttackType attackCalculate(const Attributes& attr, UIntegerType) const override {

        return 20 + 1.1*attr.strength() + 0.2*attr.dexterity() + 0.1*attr.wisdom();
    }
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
