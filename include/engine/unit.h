
#ifndef UNIT_H
#define UNIT_H

#include "unitbase.h"
#include "battlewidget.h"

/*!
 * \brief Class that represents an unit in the engine
 * \sa BattleEngine, UnitBase, UnitInfo, UnitAnimationItem
 */
class Unit final : public UnitBase {

    using Base = UnitBase;

public:

    class Observer;

    struct EffectInfo;

    using ObserversList = std::vector<Observer *>;
    using EffectsList = std::vector<std::pair<const UnitEffect *, EffectInfo> >;

    /*!
     * \brief Construct an Unit object
     * \param info UnitInfo with the information about this unit type
     * \param controller Controller that will be used to select skills to perform
     * \param m EngineMap where the unit is
     * \param team Team of the unit
     * \param i BattleWidget object, it's used to receive user input when the controller asks for
     */
    Unit(const UnitInfo *info, UnitController *controller, EngineMap *m, UIntegerType team, BattleWidget *i);

    ~Unit() final;

    bool needThreadToAct() final {

        if(isDead() || isPerformingSkill()) return false;

        return !controller()->isFast();
    }

    /*!
     * \brief Return the team of the unit
     * \return Unit's team
     */
    UIntegerType team() const { return _team; }

    /*!
     * \brief The unit calling this method will attack the 'target'
     * \brief u->attack(target, damage) effectively calls target->receiveDamage(damage, u)
     * \param target Unit that will be attacked
     * \param damage Damage of the attack
     * \sa receiveDamage(AttackType, Unit *)
     * \return true if the target remains alive, false otherwise
     */
    bool attack(Unit *target, AttackType damage) { return target->receiveDamage(damage, this); }

    /*!
     * \brief The unit received damage
     * \param damage Damage amount(effects can modify it)
     * \param attacking The unit that is attacking, nullptr the damage was not caused by other unit, by default nullptr
     * \return true if the unit remains alive, false otherwise
     */
    bool receiveDamage(AttackType damage, Unit *attacking = nullptr);

    /*!
     * \brief The unit calling this method will heal 'target'
     * \brief u->heal(target, amount) effectively calls target->healed(amount, u)
     * \param target Unit that will be healed
     * \param amount Amount of health that will be healed
     */
    void heal(Unit *target, HealthType amount) { target->healed(amount, this); }

    /*!
     * \brief The unit was healed
     * \param amount Amount of health that was healed
     * \param healing Unit that healed
     */
    void healed(HealthType amount, Unit *healing = nullptr);

    /*!
     * \brief Consume some energy, if has not enough energy, it fails without sonsuming any energy
     * \param energy The amount of energy that will be consumed
     * \return true if the energy is consumed, false if it fails
     */
    bool consumeEnergy(EnergyType energy);

    /*!
     * \brief Verify if the unit is dead
     * \return true if the unit is dead, false otherwise
     */
    bool isDead() const { return health() <= 0; }

    /*!
     * \brief Attach an observer to this unit, it will be notified for some unit events, like if it dies
     * \param ob Observer that will be attached
     * \return true if 'ob' was added successfully, false if it is already observing this unit
     */
    bool attachObserver(Observer *ob);

    /*!
     * \brief Detach an observer of this unit
     * \param ob Observer that will be detached
     * \return true if it was detached, false if it was not an observer of the unit
     */
    bool detachObserver(Observer *ob);

    /*!
     * \brief Detach all of the observers of the unit
     */
    void detachAllObservers() { _observers.clear(); }

    /*!
     * \brief Return the list of all the observers of the unit
     * \return List with all the observers
     */
    const ObserversList& observers() const { return _observers; }

    /*!
     * \brief Add a permanent effect to this unit
     * \param effect Effect that will be added
     * \return Always return true
     */
    bool addEffect(const UnitEffect *effect) { return addEffect(effect, std::numeric_limits<UIntegerType>::max(), true); }

    /*!
     * \brief Add a effect to this unit
     * \param effect Effect that will be added
     * \param duration Effect duration, the time it lasts depends on the unit speed
     * \param renew If true, after the effect's duration is over, the duration will be set to start again
     * \return Always return true
     */
    bool addEffect(const UnitEffect *effect, UIntegerType duration, bool renew = false);

    /*!
     * \brief Remove an effect from this unit, if there is more than one, only the first found will be removed
     * \param effect Effect that will be removed
     * \return true if the effect was removed, false if it was not found
     */
    bool removeEffect(const UnitEffect *effect);

    /*!
     * \brief Return a list with all the effects of the unit
     * \return A list with all the effects
     */
    const EffectsList& effects() const { return _effects; }

    /*!
     * \brief Set the x position of the unit if it's possible
     * \param x The new value for x position
     * \return true if it was able to change the position, false otherwise
     */
    bool setX(PositionType x) { return setPos(x, Base::y()); }

    /*!
     * \brief Set the y position of the unit if it's possible
     * \param y The new value for y position
     * \return true if it was able to change the position, false otherwise
     */
    bool setY(PositionType y) { return setPos(Base::x(), y); }

    /*!
     * \brief Set the position of the unit if it's possible
     * \param x The new value for x position
     * \param y The new value for y position
     * \return true if it was able to change the position, false otherwise
     */
    bool setPos(PositionType x, PositionType y) { return setPos({x, y}); }

    /*!
     * \brief Set the position of the unit if it's possible
     * \param p The new position of the unit
     * \return true if it was able to change the position, false otherwise
     */
    bool setPos(PointType p);

    /*!
     * \brief Set the unit's angle
     * \param angle New angle value, in radians
     * \return Always true
     */
    bool setAngle(AngleType angle);

    /*!
     * \brief If it's performing a skill, perform, if it's not, choose
     * \sa choose(), perform()
     * \return false if it was unable to act, true otherwise
     */
    bool act() final;

    /*!
     * \brief Ask the controller to choose a skill and if needed, an angle
     * \return Always return true
     */
    bool choose();

    /*!
     * \brief Advance one turn of the skill beeing performed
     * \return false if the skill is over, true otherwise
     */
    bool perform();

    /*!
     * \brief Notify the observers that this unit was selected
     */
    void select();

    /*!
     * \brief Notify the observers that this unit was unselected
     */
    void unselect();

    /*!
     * \brief Verify if the unit is performing a skill
     * \return true if it is, false otherwise
     */
    bool isPerformingSkill() const { return _skill < unitInfo()->skills(); }

    /*!
     * \brief Return the id of the skill beeing performed
     * \return Id of the skill beeing performed, if none is beeing performed it will return an invalid id
     */
    UIntegerType skillId() const { return _skill; }

    /*!
     * \brief Return this unit controller
     * \return The controller of this unit
     */
    const UnitController *controller() const { return _controller; }

    /*!
     * \brief Return the maximum x and y position the unit can reach in the map
     * \return Maximum position the unit can reach
     */
    PointType maxPosition() const;

    SpeedType effectiveSpeed() const override;

    struct EffectInfo {

        UIntegerType duration;
        UIntegerType starting_duration;
        bool renew;
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
    virtual void unitEffectAdded(Unit *, const UnitEffect *) {}
    virtual void unitEffectRemoved(Unit *, const UnitEffect *) {}
};

#endif // UNIT_H
