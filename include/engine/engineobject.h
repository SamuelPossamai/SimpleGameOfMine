
#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include "enginemap.h"
#include "engineobjectbase.h"

class EngineObject : public EngineObjectBase {

    using Base = EngineObjectBase;

public:

    class Observer;

    using ObserversList = std::vector<Observer *>;

    EngineObject(const EngineObject&) = delete;

    EngineObject& operator=(const EngineObject&) = delete;

    virtual ~EngineObject() override;

    virtual bool act() = 0;

    virtual bool needThreadToAct() { return false; }

    /*!
     * \brief Attach an observer to this object, it will be notified for some events
     * \param ob Observer that will be attached
     * \return true if 'ob' was added successfully, false if it is already observing this object
     */
    bool attachObserver(Observer *ob);

    /*!
     * \brief Detach an observer of this object
     * \param ob Observer that will be detached
     * \return true if it was detached, false if it was not an observer of the object
     */
    bool detachObserver(Observer *ob);

    /*!
     * \brief Detach all of the observers of the object
     */
    void detachAllObservers() { _observers.clear(); }

    /*!
     * \brief Return the list of all the observers of the object
     * \return List with all the observers
     */
    const ObserversList& engineObjectObservers() const { return _observers; }

    /*!
     * \brief Set the x position of the object if it's possible
     * \param x The new value for x position
     * \return true if it was able to change the position, false otherwise
     */
    bool setX(PositionType x) { return setPos(x, Base::y()); }

    /*!
     * \brief Set the y position of the object if it's possible
     * \param y The new value for y position
     * \return true if it was able to change the position, false otherwise
     */
    bool setY(PositionType y) { return setPos(Base::x(), y); }

    /*!
     * \brief Set the position of the object if it's possible
     * \param x The new value for x position
     * \param y The new value for y position
     * \return true if it was able to change the position, false otherwise
     */
    bool setPos(PositionType x, PositionType y) { return setPos({x, y}); }

    /*!
     * \brief Set the position of the object if it's possible
     * \param p The new position of the object
     * \return true if it was able to change the position, false otherwise
     */
    bool setPos(PointType p);

    /*!
     * \brief Set the object's angle
     * \param angle New angle value, in radians
     * \return Always true
     */
    bool setAngle(AngleType angle);

    SpeedType speed() const = delete;
    SpeedType baseSpeed() const { return Base::speed(); }
    virtual SpeedType effectiveSpeed() const { return Base::speed(); }

protected:

    EngineObject(EngineMap *m, SizeType s, SpeedType sp, PointType pos = {0, 0}, AngleType angle = 0) :
        EngineObjectBase(s, sp, pos, angle), _map(m) {

        m->addObjectPending(this);
    }

    EngineMap *map() const { return _map; }

private:

    template <typename... Args>
    void _notifyAll(void (Observer::*ObserverMethod)(EngineObject *, Args...), Args... args) {
        for(Observer *observer : _observers) (observer->*ObserverMethod)(this, args...);
    }

    EngineMap * const _map;

    ObserversList _observers;
};

class EngineObject::Observer {

public:

    virtual void engineObjectDestroyed(EngineObject *) {}
    virtual void engineObjectMoved(EngineObject *) {}
    virtual void engineObjectRotated(EngineObject *) {}
};

#endif // ENGINEOBJECT_H
