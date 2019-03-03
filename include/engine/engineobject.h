
#ifndef ENGINEOBJECT_H
#define ENGINEOBJECT_H

#include "utility/observable.h"
#include "enginemap.h"
#include "engineobjectbase.h"

using EngineObjectObservableBase = utility::Observable<EngineObject, UIntegerType, const utility::Variant&>;

/*!
 * \brief A class that represents an object that can be managed by BattleEngine and EngineMap
 * \sa BattleEngine, EngineMap
 */
class EngineObject : public EngineObjectBase, protected EngineObjectObservableBase {

    friend EngineObjectObservableBase;

    using Base = EngineObjectBase;

public:

    using Observer = Observable::Observer;

    struct ObservedEventType;
    class ObserverWrapper;

    EngineObject(const EngineObject&) = delete;

    EngineObject& operator=(const EngineObject&) = delete;

    virtual ~EngineObject() override;

    /*!
     * \brief This is an abstract method that do the object's action, it's called
     * \return false if the object has expired, true otherwise
     */
    virtual bool act() = 0;

    /*!
     * \brief This method will warn the engine that this object needs a thread to act
     * \brief It will need a thread if it takes some time to perform the action
     * \brief If it will ask for users input, this method must return true
     * \return true if it needs a thred to act, false otherwise, by default return false
     */
    virtual bool needThreadToAct() { return false; }

    /*!
     * \brief Attach an observer to this object, it will be notified for some events
     * \param ob Observer that will be attached
     * \return true if 'ob' was added successfully, false if it is already observing this object
     */
    bool attachObserver(Observer *ob) { return attach(ob); }

    /*!
     * \brief Detach an observer of this object
     * \param ob Observer that will be detached
     * \return true if it was detached, false if it was not an observer of the object
     */
    bool detachObserver(Observer *ob) { return detach(ob); }

    /*!
     * \brief Detach all of the observers of the object
     */
    void detachAllObservers() { return detachAll(); }

    /*!
     * \brief Return the list of all the observers of the object
     * \return List with all the observers
     */
    const ObserverList& engineObjectObservers() const { return observers(); }

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

    EngineMap * const _map;
};

struct EngineObject::ObservedEventType {

public:

    enum : UIntegerType { START = 0, Moved, Rotated, END };

    ObservedEventType(UIntegerType event_type_id) : _int(event_type_id) {}
    ObservedEventType(const ObservedEventType&) = default;

    ObservedEventType& operator=(const ObservedEventType&) = default;

    operator UIntegerType() const { return _int; }

private:

    UIntegerType _int;
};

class EngineObject::ObserverWrapper : virtual protected EngineObject::Observer {

public:

    virtual ~ObserverWrapper() override = default;

    virtual void engineObjectDestroyed(const EngineObject *) {}
    virtual void engineObjectMoved(const EngineObject *) {}
    virtual void engineObjectRotated(const EngineObject *) {}

protected:

    virtual void update(const EngineObject *o, UIntegerType event_type, const utility::Variant&) override {

        switch(event_type) {

            case EngineObject::ObservedEventType::Moved:
                this->engineObjectMoved(o);
                break;
            case EngineObject::ObservedEventType::Rotated:
                this->engineObjectRotated(o);
                break;
        }
    }

    virtual void observableDestroyed(const EngineObject *o) override { this->engineObjectDestroyed(o); }
};

#endif // ENGINEOBJECT_H
