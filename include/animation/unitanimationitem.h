
#ifndef UNITANIMATIONITEM_H
#define UNITANIMATIONITEM_H

#include <QGraphicsScene>

#include "config/types.h"
#include "engine/unit.h"

/*!
 * \brief A class that is meant to be the base class to classes that will display units in the interface.
 * \brief It observes an Unit so if something happens to the unit, it can use this information to change the graphics beeing displayed
 * \sa Unit
 */
class UnitAnimationItem : public Unit::Observer {

public:

    /*!
     * \brief Creates an UnitAnimationItem, this constructor will be called by base classes
     * \brief The Unit 'u' will be attached
     * \sa Unit::attachHandler(Unit::Handler *)
     * \param u The unit that a base class object will observe and display
     */
    UnitAnimationItem(Unit *u) : _scene(nullptr), _unit(u) { u->attachObserver(this); }

    /*!
     * \brief The destructor will detach the handler
     * \sa Unit::detachHandler(Unit::Handler *)
     */
    virtual ~UnitAnimationItem() { if(_unit) _unit->detachObserver(this); }

    /*!
     * \brief This method should be called in a loop, all changes in the graphics display must be done here
     */
    virtual void redraw() = 0;

    /*!
     * \brief Set an scene where the unit will be displayed
     * \param scene Graphics scene where the unit should be displayed
     * \sa addToScene(QGraphicsScene *), removeFromScene()
     */
    void setScene(QGraphicsScene *scene) {
        if(!_scene) this->removeFromScene();
        _scene = scene;
        if(scene) this->addToScene(_scene);
    }

    /*!
     * \brief Remove from the current scene
     * \sa setScene(QGraphicsScene *)
     */
    void clearScene() { setScene(nullptr); }

    /*!
     * \brief Return the unit it is observing
     * \return The unit this object is observing
     */
    const Unit *unit() const { return _unit; }

protected:

    /*!
     * \brief Return the scene the image should be displayed
     * \return The scene where it is meant to be displayed
     */
    QGraphicsScene *scene() { return _scene; }
    const QGraphicsScene *scene() const { return _scene; }

    /*!
     * \brief This method is called when the scene is set, if it exists
     */
    virtual void addToScene(QGraphicsScene *) = 0;

    /*!
     * \brief This method is called when the scene is set, if there was other scene before
     */
    virtual void removeFromScene() = 0;

    /*!
     * \brief This method handle the destruction of the unit it is observing, so it will not try to detach later
     */
    virtual void unitObjectDestroyed(Unit *) { _unit = nullptr; }

private:

    QGraphicsScene *_scene;
    Unit *_unit;
};

#endif // UNITANIMATIONITEM_H
