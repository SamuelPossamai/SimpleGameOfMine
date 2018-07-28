
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

    struct EffectInfo;

    using ObserversList = std::vector<Observer *>;
    using EffectsList = std::vector<std::pair<const UnitEffect *, EffectInfo> >;

    Unit(const UnitInfo *info, UnitController *controller, Map *m, UIntegerType team, BattleWidget *i);

    ~Unit();

    UIntegerType team() const { return _team; }

    bool attack(Unit *target, AttackType damage) { return target->receiveDamage(damage, this); }
    bool receiveDamage(AttackType damage, Unit *attacking = nullptr);

    void heal(Unit *target, HealthType amount) { target->healed(amount, this); }
    void healed(HealthType amount, Unit *healing = nullptr);

    bool consumeEnergy(EnergyType energy);

    bool isDead() const { return health() <= 0; }

    bool attachObserver(Observer *h);
    bool detachObserver(Observer *h);
    void detachAllObservers() { _observers.clear(); }
    const ObserversList& observers() const { return _observers; }

    bool addEffect(const UnitEffect *effect) { return addEffect(effect, std::numeric_limits<UIntegerType>::max(), true); }
    bool addEffect(const UnitEffect *effect, UIntegerType duration, bool renew = false);
    bool removeEffect(const UnitEffect *effect);

    const EffectsList& effects() const { return _effects; }

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

    PointType maxPosition() const;

    struct EffectInfo {

        UIntegerType duration;
        UIntegerType starting_duration;
    };

private:

    template <typename... Args>
    void _notifyAll(void (Observer::*ObserverMethod)(Unit *, Args...), Args... args) {
        for(Observer *observer : _observers) (observer->*ObserverMethod)(this, args...);
    }

    bool _choose_internal(BattleWidget::InputInterface&);
    void _verify_effects();

    UIntegerType _team;
    ObserversList _observers;
    UnitController * const _controller;
    Map * const _map;

    UIntegerType _skill_step;
    AngleType _skill_angle;
    UIntegerType _skill_next_call;
    UIntegerType _skill;

    EffectsList _effects;

    UnitAnimationItem *_gitem;

    BattleWidget *_interface;
};

class Unit::Observer {

public:

    virtual void unitSkillStarted(Unit *) {}
    virtual void unitSkillAdvance(Unit *) {}
    virtual void unitSkillFinished(Unit *) {}
    virtual void unitReceivedDamage(Unit *) {}
    virtual void unitHealed(Unit *) {}
    virtual void unitMoved(Unit *) {}
    virtual void unitRotated(Unit *) {}
    virtual void unitDeathEvent(Unit *) {}
    virtual void unitObjectDestroyed(Unit *) {}
    virtual void unitSelected(Unit *) {}
    virtual void unitUnselected(Unit *) {}
    virtual void unitEnergyConsumed(Unit *) {}
};

#endif // UNIT_H
