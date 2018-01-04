#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include "animation.h"

class AnimatedObject : public QGraphicsPixmapItem {

public:

    AnimatedObject() : _cur_animation(0), _idle_animation(0) { }

    UIntegerType addAnimation(const Animation& animation) { _animations.push_back(animation); return _animations.size() - 1; }
    void switchAnimation(UIntegerType pos, const Animation& animation) { _animations[pos] = animation; }

    void selectAnimation(UIntegerType n);
    UIntegerType currentAnimation() const { return _cur_animation; }

    UIntegerType animations() const { return _animations.size(); }

    void setIdleAnimation(UIntegerType idle_animation) { _idle_animation = idle_animation; }

    UIntegerType idleAnimation() const { return _idle_animation; }

    void step();

    void next() { step(); }

private:

    UIntegerType _cur_animation;
    UIntegerType _idle_animation;
    std::vector<Animation> _animations;
};


#endif // ANIMATEDOBJECT_H
