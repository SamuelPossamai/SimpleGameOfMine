#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include "animation.h"

class AnimatedObject : public Animation::Object {

    using Object = Animation::Object;

public:

    explicit AnimationObject(PositionType x = 0, PositionType y = 0, PositionType angle = 0) :
        Object(x, y, angle), _cur_animation(0), _idle_animation(0) {}

    UIntegerType addAnimation(const Animation& animation) const { _animations.push_back(animation); return _animations.size() - 1; }

    void selectAnimation(UIntegerType n) { _cur_animation = n; }
    UIntegerType currentAnimation() const { return _cur_animation; }

    UIntegerType animations() const { return _animations.size(); }

    void setIdleAnimation(UIntegerType idle_animation) { _idle_animation = idle_animation; }

    UIntegerType idleAnimation() const { return _idle_animation; }

private:

    UIntegerType _cur_animation;
    UIntegerType _idle_animation;
    std::vector<Animation> _animations;
};


#endif // ANIMATEDOBJECT_H
