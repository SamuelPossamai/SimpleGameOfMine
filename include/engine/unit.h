
#ifndef UNIT_H
#define UNIT_H

#include "unitbase.h"

class Unit : public UnitBase {

    using Base = UnitBase;

public:

    Unit(const UnitInfo *info, UIntegerType team, QWidget *w) : Base(info, w), _team(team) {}

    UIntegerType team() const { return _team; }

private:

    UIntegerType _team;
};

#endif // UNIT_H
