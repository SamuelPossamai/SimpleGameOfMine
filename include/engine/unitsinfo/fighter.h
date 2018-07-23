
#ifndef UNITSINFO_FIGHTER_H
#define UNITSINFO_FIGHTER_H

#include <memory/onecopymemorymanager.h>

#include "unitsinfo/unitclassinfo.h"

namespace unitsinfo {

class Fighter : public UnitClassInfo {

    friend class OneCopyMemoryManager<Fighter>;

    using MemoryManager = OneCopyMemoryManager<Fighter>;

    Fighter(const Attributes& attr);

    virtual HealthType healthCalculate() const override { return 1000 + 10*attributes().vitality(); }
    virtual AttackType attackCalculate() const override { return 20 + attributes().strength() + attributes().dexterity()/3; }
    virtual SpeedType speedCalculate() const override { return 60 + attributes().agility() + 3*attributes().dexterity()/4; }

public:

    virtual ~Fighter();

    static Fighter *getInfo(Attributes attr) { return _copies.get(attr); }

private:

    static MemoryManager _copies;
};

} /* namespace creature */

#endif // UNITSINFO_FIGHTER_H
