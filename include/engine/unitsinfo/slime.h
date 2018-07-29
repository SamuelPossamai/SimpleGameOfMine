
#ifndef UNITSINFO_SLIME_H
#define UNITSINFO_SLIME_H

#include <memory/onecopymemorymanager.h>

#include "unitinfo.h"

namespace unitsinfo {

class Slime : public UnitInfo {

public:

    enum class Type : UIntegerType { Normal, Fast, Immortal, Crazy, Ghost };

    virtual ~Slime();

    static Slime *getInfo(UIntegerType level, const Type& type = Type::Normal) { return _memmanager.get(Slime(level, type)); }

    bool operator <(const Slime& other) const {

        if(_type != other._type) return _type < other._type;

        return _level < other._level;
    }

    virtual void init(Unit *u) const override;

private:

    Slime(UIntegerType level, const Type& type);

    Type _type;
    UIntegerType _level;

    static OneCopyMemoryManager<Slime> _memmanager;
};

} /* namespace creature */

#endif // UNITSINFO_SLIME_H
