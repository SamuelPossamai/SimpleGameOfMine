
#ifndef UNITANIMATIONITEM_H
#define UNITANIMATIONITEM_H

#include "config/types.h"
#include "engine/unit.h"
#include "animationitembase.h"

/*!
 * \brief A class that is meant to be the base class to classes that will display units in the interface.
 * \brief It observes an Unit so if something happens to the unit, it can use this information to change the graphics beeing displayed
 * \sa Unit
 */
class UnitAnimationItem : public AnimationItemBase, public Unit::Observer {

public:

    /*!
     * \brief Creates an UnitAnimationItem, this constructor will be called by base classes
     * \brief The Unit 'u' will be attached
     * \sa Unit::attachHandler(Unit::Handler *)
     * \param u The unit that a base class object will observe and display
     */
    explicit UnitAnimationItem(Unit *u) : _unit(u) { u->attachObserver(this); }

    /*!
     * \brief The destructor will detach the handler
     * \sa Unit::detachHandler(Unit::Handler *)
     */
    virtual ~UnitAnimationItem() { if(_unit) _unit->detachObserver(this); }

    /*!
     * \brief Return the unit it is observing
     * \return The unit this object is observing
     */
    const Unit *unit() const { return _unit; }

protected:

    /*!
     * \brief This method handle the destruction of the unit it is observing, so it will not try to detach later
     */
    virtual void unitObjectDestroyed(Unit *) { _unit = nullptr; }

private:

    Unit *_unit;
};

#endif // UNITANIMATIONITEM_H
