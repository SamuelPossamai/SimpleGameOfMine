
#ifndef UNITSINFO_KNIGHT_H
#define UNITSINFO_KNIGHT_H

#include <memory/onecopymemorymanager.h>

#include "unitsinfo/unitclassinfo.h"

namespace unitsinfo {

class Knight : public UnitClassInfo {

    friend class OneCopyMemoryManager<Knight>;

    using MemoryManager = OneCopyMemoryManager<Knight>;

protected:

    Knight(const Attributes& attr);

    virtual HealthType healthCalculate() const override { return 300 + 20*attributes().vitality() + 0.1*attributes().strength(); }
    virtual EnergyType energyCalculate() const override { return 10 + attributes().wisdom() + attributes().vitality(); }
    virtual AttackType attackCalculate() const override {

        return 16 + 0.85*attributes().strength() + 0.1*attributes().dexterity() + 0.2*attributes().wisdom();
    }
    virtual SpeedType speedCalculate() const override;
    virtual SizeType sizeCalculate() const override { return 28; }

public:

    virtual ~Knight();

    static Knight *getInfo(Attributes attr) { return _copies.get(attr); }

private:

    static MemoryManager _copies;
};

} /* namespace unitsinfo */

#endif // UNITSINFO_KNIGHT_H
