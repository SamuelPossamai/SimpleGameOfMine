
#ifndef UNITSINFO_NINJA_H
#define UNITSINFO_NINJA_H

#include <memory/onecopymemorymanager.h>

#include "unitsinfo/fighter.h"

namespace unitsinfo {

class Ninja : public Fighter {

    friend class OneCopyMemoryManager<Ninja>;

    using MemoryManager = OneCopyMemoryManager<Ninja>;

    Ninja(const Attributes& attr);

    virtual HealthType healthCalculate() const override { return 150 + 5*attributes().vitality() + attributes().dexterity(); }
    virtual AttackType attackCalculate() const override { return 12 + 0.75*attributes().strength() + attributes().dexterity()/2; }
    virtual SpeedType speedCalculate() const override { return 80 + 1.25*attributes().agility() + 3*attributes().dexterity()/4; }

public:

    virtual ~Ninja() {}

    static Ninja *getInfo(Attributes attr) { return _copies.get(attr); }

private:

    static MemoryManager _copies;
};

} /* namespace creature */

#endif // UNITSINFO_NINJA_H
