
#ifndef UNIT_H
#define UNIT_H

#include "unitbase.h"
#include "battlewidget.h"

class Unit : public UnitBase {

    using Base = UnitBase;

public:

    class Handler;

    using HandlersList = std::vector<Handler *>;

    Unit(const UnitInfo *info, UnitController *controller, Map *m, UIntegerType team, BattleWidget *i) :
        Base(info), _team(team), _controller(controller), _map(m), _skill(info->skills()), _interface(i) {}

    ~Unit();

    UIntegerType team() const { return _team; }

    bool receiveDamage(AttackType);

    bool isDead() const { return health() <= 0; }

    void attachHandler(Handler *h) { _handlers.push_back(h); }
    void detachHandler(Handler *h);
    void detachAllHandlers() { _handlers.clear(); }
    const HandlersList& handlers() const { return _handlers; }

    bool setX(PositionType x) { return setPos(x, Base::y()); }
    bool setY(PositionType y) { return setPos(Base::x(), y); }

    bool setPos(PositionType x, PositionType y) { return setPos({x, y}); }
    bool setPos(PointType p);

    bool setAngle(AngleType angle);

    bool act();
    bool choose();
    bool perform();

    void select();
    void unselect();

    bool isPerformingSkill() const { return _skill < unitInfo()->skills(); }
    UIntegerType skillId() const { return _skill; }

    const UnitController *controller() const { return _controller; }

private:

    template <typename... Args>
    void _notifyAll(void (Handler::*HandlerMethod)(Unit *, Args...), Args... args) {
        for(Handler *handler : _handlers) (handler->*HandlerMethod)(this, args...);
    }

    UIntegerType _team;
    HandlersList _handlers;
    UnitController * const _controller;
    Map * const _map;

    UIntegerType _skill_step;
    AngleType _skill_angle;
    UIntegerType _skill_next_call;
    UIntegerType _skill;

    BattleWidget *_interface;
};

class Unit::Handler {

public:

    virtual void unitHandlerSkillStarted(Unit *) {}
    virtual void unitHandlerSkillFinished(Unit *) {}
    virtual void unitHandlerReceivedDamage(Unit *) {}
    virtual void unitHandlerMoved(Unit *) {}
    virtual void unitHandlerRotated(Unit *) {}
    virtual void unitHandlerDeathEvent(Unit *) {}
    virtual void unitHandlerObjectDestroyed(Unit *) {}
    virtual void unitHandlerSelected(Unit *) {}
    virtual void unitHandlerUnselected(Unit *) {}
};

#endif // UNIT_H
