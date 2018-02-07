#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include "animationhandler.h"

/*!
 * \brief A graphics item used to display animations.
 * \sa Animation
 */
class AnimatedObject : public QGraphicsPixmapItem {

public:

    /*!
     * \brief Construct an AnimatedObject without any animation
     */
    AnimatedObject() : _cur_animation(0), _idle_animation(0) { }

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

private:

    void _update() { _animation_h.setAnimation(&_animations[_cur_animation]); }

    UIntegerType _cur_animation;
    UIntegerType _idle_animation;
    std::vector<Animation> _animations;

    AnimationHandler _animation_h;
};


#endif // ANIMATEDOBJECT_H
