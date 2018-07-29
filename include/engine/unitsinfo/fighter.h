
#ifndef UNITSINFO_FIGHTER_H
#define UNITSINFO_FIGHTER_H

#include <memory/onecopymemorymanager.h>

#include "unitsinfo/unitclassinfo.h"

namespace unitsinfo {

class Fighter : public UnitClassInfo {

    friend class OneCopyMemoryManager<Fighter>;

    using MemoryManager = OneCopyMemoryManager<Fighter>;

protected:

    Fighter(const Attributes& attr);

    virtual HealthType healthCalculate() const override { return 200 + 12*attributes().vitality() + 0.25*attributes().strength(); }
    virtual EnergyType energyCalculate() const override { return 0; }
    virtual AttackType attackCalculate() const override {

        return 20 + 1.1*attributes().strength() + 0.2*attributes().dexterity() + 0.1*attributes().wisdom();
    }
    virtual SpeedType speedCalculate() const override { return 55 + 0.75*attributes().agility() + 0.25*attributes().dexterity(); }
    virtual SizeType sizeCalculate() const override { return 25; }

public:

    virtual ~Fighter();

    static Fighter *getInfo(Attributes attr) { return _copies.get(attr); }

private:

    static MemoryManager _copies;
};

} /* namespace unitsinfo */

#endif // UNITSINFO_FIGHTER_H
