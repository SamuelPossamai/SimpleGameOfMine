
#ifndef UNIT_H
#define UNIT_H

#include "unitbase.h"
#include "battlewidget.h"

/*!
 * \brief Class that represents an unit in the engine
 * \sa BattleEngine, UnitBase, UnitInfo, UnitAnimationItem
 */
class Unit : public UnitBase {

    using Base = UnitBase;

public:

    class Observer;

    using ObserversList = std::vector<Observer *>;

    Unit(const UnitInfo *info, UnitController *controller, Map *m, UIntegerType team, BattleWidget *i);

    ~Unit();

    void setScene(QGraphicsScene *scene);

    UIntegerType team() const { return _team; }

    bool receiveDamage(AttackType);

    bool isDead() const { return health() <= 0; }

    void attachObserver(Observer *h) { _observers.push_back(h); }
    void detachObserver(Observer *h);
    void detachAllObservers() { _observers.clear(); }
    const ObserversList& observers() const { return _observers; }

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

    void redraw();

    bool isPerformingSkill() const { return _skill < unitInfo()->skills(); }
    UIntegerType skillId() const { return _skill; }

    const UnitController *controller() const { return _controller; }

private:

    template <typename... Args>
    void _notifyAll(void (Observer::*ObserverMethod)(Unit *, Args...), Args... args) {
        for(Observer *observer : _observers) (observer->*ObserverMethod)(this, args...);
    }

    UIntegerType _team;
    ObserversList _observers;
    UnitController * const _controller;
    Map * const _map;

    UIntegerType _skill_step;
    AngleType _skill_angle;
    UIntegerType _skill_next_call;
    UIntegerType _skill;

    UnitAnimationItem *_gitem;

    BattleWidget *_interface;
};

class Unit::Observer {

public:

    virtual void unitSkillStarted(Unit *) {}
    virtual void unitSkillAdvance(Unit *) {}
    virtual void unitSkillFinished(Unit *) {}
    virtual void unitReceivedDamage(Unit *) {}
    virtual void unitMoved(Unit *) {}
    virtual void unitRotated(Unit *) {}
    virtual void unitDeathEvent(Unit *) {}
    virtual void unitObjectDestroyed(Unit *) {}
    virtual void unitSelected(Unit *) {}
    virtual void unitUnselected(Unit *) {}
};

#endif // UNIT_H
