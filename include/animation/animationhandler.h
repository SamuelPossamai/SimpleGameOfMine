#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include "animation.h"

/*!
 * \brief The AnimationHandler class is used to manage the current pixmap image that is meant to be displayed based on the animation
 * \sa Animation, AnimatedObject
 */
class AnimationHandler {

public:

    AnimationHandler(Animation *animation = nullptr) : _animation(animation), _cur_step((animation) ? animation->steps() : 0),
        _vec_pos(0) { }

    void setAnimation(Animation *animation) {

        _animation = animation;
        _vec_pos = 0;
        _cur_step = (animation) ? animation->steps() : 0;
    }

    const Animation *animation() const { return _animation; }

    bool next();

    bool step() { return next(); }

    void start(bool rnd_start = true);

    void restart(bool rnd_start = false) { start(rnd_start); }

    bool isOver() const { return _cur_step >= _animation->steps(); }

    void forceOver();

    QPixmap pixmap() const;

private:

    bool _choose_item();

    Animation *_animation;

    UIntegerType _cur_step;
    UIntegerType _vec_pos;
};

#endif // ANIMATIONHANDLER_H
