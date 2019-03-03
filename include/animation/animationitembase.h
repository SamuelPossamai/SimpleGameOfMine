
#ifndef ANIMATIONITEMBASE_H
#define ANIMATIONITEMBASE_H

#include <QGraphicsScene>

#include "engineobject.h"

class AnimationItemBase : virtual public EngineObject::ObserverWrapper {

public:

    /*!
     * \brief Creates an AnimationItemBase
     */
    AnimationItemBase(EngineObject *obj) : _scene(nullptr) { obj->attachObserver(this); }

    virtual ~AnimationItemBase() override = default;

    /*!
     * \brief This method should be called in a loop, all changes in the graphics display must be done here
     * \return false if the animation is over, true otherwise
     */
    virtual bool redraw() = 0;

    /*!
     * \brief Set an scene where the item will be displayed
     * \param scene Graphics scene where the item should be displayed
     * \sa addToScene(QGraphicsScene *), removeFromScene()
     */
    void setScene(QGraphicsScene *scene) {
        if(_scene) this->removeFromScene();
        _scene = scene;
        if(scene) this->addToScene(_scene);
    }

    /*!
     * \brief Remove from the current scene
     * \sa setScene(QGraphicsScene *)
     */
    void clearScene() { setScene(nullptr); }

    const EngineObject *object() const { return const_cast<AnimationItemBase *>(this)->accessObject(); }

protected:

    EngineObject *accessObject() {

        auto& observeds = Observer::observeds();

        if(observeds.empty()) return nullptr;

        return observeds.front();
    }

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

private:

    QGraphicsScene *_scene;
};

#endif // ANIMATIONITEMBASE_H
