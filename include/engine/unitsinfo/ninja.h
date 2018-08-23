
#ifndef UNITSINFO_NINJA_H
#define UNITSINFO_NINJA_H

#include <memory/onecopymemorymanager.h>

#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Ninja : public Fighter {

    friend class OneCopyMemoryManager<Ninja>;

    using MemoryManager = OneCopyMemoryManager<Ninja>;

    Ninja(const Attributes& attr);

    virtual HealthType healthCalculate() const override { return 150 + 8*attributes().vitality() + 0.2*attributes().dexterity(); }
    virtual EnergyType energyCalculate() const override { return 100 + 5*attributes().wisdom() + attributes().dexterity(); }
    virtual AttackType attackCalculate() const override {

        return 12 + 0.8*attributes().strength() + 0.3*attributes().dexterity() +
                0.1*attributes().agility() + 0.1*attributes().wisdom();
    }
    virtual SpeedType speedCalculate() const override { return 80 + 1*attributes().agility() + 0.4*attributes().dexterity(); }
    virtual SizeType sizeCalculate() const override {

        SizeType size = Fighter::sizeCalculate() - 0.01*(attributes().dexterity() + attributes().agility());
        return size > 5 ? size : 5;
    }

public:

    virtual ~Ninja() {}

    static Ninja *getInfo(Attributes attr) { return _copies.get(attr); }

private:

    static MemoryManager _copies;
};

} /* namespace creature */

#endif // UNITSINFO_NINJA_H
