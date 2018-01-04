
#ifndef UNIT_H
#define UNIT_H

#include "traits.h"
#include "unitbase.h"

class Unit : public UnitBase {

    using Base = UnitBase;

public:

    Unit(const UnitInfo *info, UIntegerType team) : Base(info), _team(team) {}

    UIntegerType team() const { return _team; }

private:

    UIntegerType _team;
};

#endif // UNIT_H
