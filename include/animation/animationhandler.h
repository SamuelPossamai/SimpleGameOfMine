
#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include "animation.h"

/*!
 * \brief The AnimationHandler class is used to manage the current pixmap image that is meant to be displayed based on the animation
 * \sa Animation, AnimatedObject
 */
class AnimationHandler {

public:

    /*!
     * \brief
     * \param animation
     */
    AnimationHandler(Animation *animation = nullptr) : _animation(animation), _cur_step((animation) ? animation->steps() : 0),
        _vec_pos(0) { }

    /*!
     * \brief Set a new animation, the state of this object will be set to 'over'
     * \param animation The new animation that will be handled by this object
     * \sa animation(), start()
     */
    void setAnimation(Animation *animation) {

        _animation = animation;
        _vec_pos = 0;
        _cur_step = (animation) ? animation->steps() : 0;
    }

    /*!
     * \brief Return the current animation
     * \sa setAnimation()
     * \return The current animation
     */
    const Animation *animation() const { return _animation; }

    /*!
     * \brief Advance the current animation step
     * \sa start(), isOver()
     * \return false if it's over, true otherwise
     */
    bool next();

    /*!
     * \brief Advance the current animation step, same as next()
     * \sa next()
     * \return false if it's over, true otherwise
     */
    bool step() { return next(); }

    /*!
     * \brief Start the animation display
     * \brief If the flag for animation random start is set and rnd_start is true, it will start at a random step
     * \sa next(), isOver()
     * \param rnd_start If false, random start is disabled, by default true
     */
    void start(bool rnd_start = true);

    /*!
     * \brief Start the animation display
     * \brief If the flag for animation random start is set an rnd_start is true, it will start at a random step
     * \sa start(), next(), isOver()
     * \param rnd_start If false, random start is disabled, by default false
     */
    void restart(bool rnd_start = false) { start(rnd_start); }

    /*!
     * \brief Return true if the animation is over, false otherwise
     * \sa forceOver(), next(), start()
     * \return true if animation is over, false othewise
     */
    bool isOver() const { return _cur_step >= _animation->steps(); }

    /*!
     * \brief Force the animation to end
     * \sa isOver(), next(), start()
     */
    void forceOver();

    /*!
     * \brief Return the pixmap for the current step in the animation
     * \return THe pixmap for the current step in the animation
     */
    QPixmap pixmap() const;

private:

    bool _choose_item();

    Animation *_animation;

    UIntegerType _cur_step;
    UIntegerType _vec_pos;
};

#endif // ANIMATIONHANDLER_H
