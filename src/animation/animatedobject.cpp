
#include "animatedobject.h"

void AnimatedObject::step(){


    if(_animations[_cur_animation].isOver()) selectAnimation(_idle_animation);
    else if(_animations[_cur_animation].next()) {

        auto&& pixmap = _animations[_cur_animation].pixmap();

        setPixmap(pixmap);
        setOffset(-pixmap.width()/2, -pixmap.height()/2);
    }
}

void AnimatedObject::selectAnimation(UIntegerType n) {

    _cur_animation = n;

    _animations[n].start();

    auto&& pixmap = _animations[n].pixmap();

    setPixmap(pixmap);

    setOffset(-pixmap.width()/2, -pixmap.height()/2);
}
