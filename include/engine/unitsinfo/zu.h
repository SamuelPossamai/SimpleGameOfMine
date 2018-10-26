
#ifndef UNITSINFO_ZU_H
#define UNITSINFO_ZU_H

#include "unitinfo.h"

namespace unitsinfo {

class Zu : public UnitInfo {

    Zu();

public:

    virtual ~Zu();

    static Zu *getInfo() {

        if(_info) return _info;

        _info = new Zu;

        return _info;
    }

protected:

    virtual HealthType healthCalculate(const Attributes&, UIntegerType level) const override { return 100 + 10*level; }
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const override { return 0; }
    virtual AttackType attackCalculate(const Attributes&, UIntegerType level) const override { return 5 + 1*level; }
    virtual SpeedType speedCalculate(const Attributes&, UIntegerType level) const override { return 60 + level; }
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const override { return 22; }

private:

    static Zu *_info;
};

} /* namespace creature */

#endif // UNITSINFO_ZU_H
