
#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <QGraphicsItem>

#include "animationhandler.h"

/*!
 * \brief A graphics item used to display animations.
 * \sa Animation
 */
class AnimatedObject : public QGraphicsPixmapItem {

public:

    /*!
     * \brief Class used to handle AnimatedObject events.
     * \brief To handle events from AnimatedObject you should create an class that inherits from this class.
     */
    class Handler;

    /*!
     * \brief Construct an AnimatedObject without any animation
     */
    AnimatedObject() : _cur_animation(0), _idle_animation(0), _handler(nullptr) { }

    /*!
     * \brief Used to add an animation to the list of animations this item can display
     * \sa switchAnimation(UIntegerType, const Animation&), animations()
     * \param animation this parameter is the animation that will be added to the list
     * \return The id number of the animation in the list will nbe returned
     */
    UIntegerType addAnimation(const Animation& animation);

    /*!
     * \brief Used to switch an animation from the list for another one
     * \sa addAnimation(const Animation&)
     * \param id the id of the animation that will be replaced
     * \param animation the animations that will replace the previous one
     */
    void switchAnimation(UIntegerType id, const Animation& animation) { _animations[id] = animation; }

    /*!
     * \brief Used to select the animation that will run next
     * \param id the selected animations's id number
     */
    void selectAnimation(UIntegerType id);

    /*!
     * \brief Return the id of the animation that is running
     * \return running animation's id
     */
    UIntegerType currentAnimation() const { return _cur_animation; }

    /*!
     * \brief Return the number of animations this object possess
     * \sa addAnimation(const Animation&)
     * \return Size of the animations list
     */
    UIntegerType animations() const { return _animations.size(); }

    /*!
     * \brief Clear the container that contains the animations
     * \sa addAnimation(const Animation&), animations()
     */
    void clearAnimations() { _cur_animation = _idle_animation = 0; _animations.clear(); }

    /*!
     * \brief Select which animation run whenever an the current animation is over
     * \sa idleAnimation(), selectAnimation(UIntegerType), currentAnimation()
     * \param idle_animation the animation that will be the new idle animation
     */
    void setIdleAnimation(UIntegerType idle_animation) { _idle_animation = idle_animation; }

    /*!
     * \brief Return the idle animation's id
     * \sa setIdleAnimation(UIntegerType)
     * \return The idle animation's id
     */
    UIntegerType idleAnimation() const { return _idle_animation; }

    /*!
     * \brief Advance an step in the animation, it may change the current image
     * \sa Animation, next()
     */
    void step();

    /*!
     * \brief Same as 'step'
     * \sa step()
     */
    void next() { step(); }

    /*!
     * \brief Set a class to handle this object events.
     * \sa handler()
     * \param handler class that inherit from Handler, will handle events from this object.
     */
    void setHandler(Handler *handler) { _handler = handler; }

    /*!
     * \brief Return a pointer to this object handler.
     * \return Pointer to this object event handler.
     */
    const Handler *handler() const { return _handler; }

protected:

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

private:

    void _update() { _animation_h.setAnimation(&_animations[_cur_animation]); }

    UIntegerType _cur_animation;
    UIntegerType _idle_animation;
    std::vector<Animation> _animations;

    AnimationHandler _animation_h;

    Handler *_handler;
};

class AnimatedObject::Handler {

public:

    virtual void animatedObjectMouseDoubleClickEvent(QGraphicsSceneMouseEvent *) {}
    virtual void animatedObjectMouseMoveEvent(QGraphicsSceneMouseEvent *) {}
    virtual void animatedObjectMousePressEvent(QGraphicsSceneMouseEvent *) {}
    virtual void animatedObjectMouseReleaseEvent(QGraphicsSceneMouseEvent *) {}
};

#endif // ANIMATEDOBJECT_H
