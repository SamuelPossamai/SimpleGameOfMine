
#ifndef UNIT_H
#define UNIT_H

#include "unitbase.h"

class Unit : public UnitBase {

    using Base = UnitBase;

public:

    class Handler;

    Unit(const UnitInfo *info, UIntegerType team, QWidget *w) : Base(info, w), _team(team), _handler(nullptr) {}

    UIntegerType team() const { return _team; }

    bool receiveDamage(AttackType);

    bool isDead() const { return health() <= 0; }

    void setHandler(Handler *h) { _handler = h; }
    const Handler *handler() const { return _handler; }

private:

    UIntegerType _team;
    Handler *_handler;
};

class Unit::Handler {

public:

    virtual void unitHandlerDeathEvent(Unit *) {}
};

#endif // UNIT_H
