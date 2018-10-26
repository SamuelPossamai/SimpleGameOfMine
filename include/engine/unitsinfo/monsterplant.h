
#ifndef UNITSINFO_MONSTERPLANT_H
#define UNITSINFO_MONSTERPLANT_H

#include "unitinfo.h"

namespace unitsinfo {

class MonsterPlant : public UnitInfo {

    MonsterPlant();

public:

    virtual ~MonsterPlant();

    static MonsterPlant *getInfo() {

        if(_info) return _info;

        _info = new MonsterPlant;

        return _info;
    }

protected:

    virtual HealthType healthCalculate(const Attributes&, UIntegerType level) const override { return 400 + 35*level; }
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual AttackType attackCalculate(const Attributes&, UIntegerType level) const override { return 15 + 1.2*level; }
    virtual SpeedType speedCalculate(const Attributes&, UIntegerType level) const override { return 60 + level; }
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 30; }

private:

    static MonsterPlant *_info;
};

} /* namespace creature */

#endif // UNITSINFO_MONSTERPLANT_H
