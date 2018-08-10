
#ifndef UNITSINFO_MONSTERPLANT_H
#define UNITSINFO_MONSTERPLANT_H

#include <memory/onecopymemorymanager.h>

#include "unitinfo.h"

namespace unitsinfo {

class MonsterPlant : public UnitInfo {

    MonsterPlant(UIntegerType level);

public:

    virtual ~MonsterPlant();

    static MonsterPlant *getInfo(UIntegerType level) { return _memmanager.get(MonsterPlant(level)); }

    bool operator <(const MonsterPlant& other) const { return _level < other._level; }

private:

    UIntegerType _level;

    static OneCopyMemoryManager<MonsterPlant> _memmanager;
};

} /* namespace creature */

#endif // UNITSINFO_MONSTERPLANT_H
