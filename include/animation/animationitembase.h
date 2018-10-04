
#ifndef ANIMATIONITEMBASE_H
#define ANIMATIONITEMBASE_H

#include <QGraphicsScene>

class AnimationItemBase {

public:

    /*!
     * \brief Creates an AnimationItemBase
     */
    AnimationItemBase() : _scene(nullptr) {}

    /*!
     * \brief This method should be called in a loop, all changes in the graphics display must be done here
     */
    virtual void redraw() = 0;

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

private:

    QGraphicsScene *_scene;
};

#endif // ANIMATIONITEMBASE_H
