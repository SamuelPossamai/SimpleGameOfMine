#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include <random>

#include "animation.h"

class AnimationHandler {

public:

    AnimationHandler(Animation *animation = nullptr) : _animation(animation), _cur_step((animation) ? animation->steps() : 0),
        _vec_pos(0) { }

    void setAnimation(Animation *animation) { _animation = animation; }
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

    static std::mt19937 _gen;
};

#endif // ANIMATIONHANDLER_H
