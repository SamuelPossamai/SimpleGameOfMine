
#include <QGraphicsScene>

#include "animatedobject.h"

void AnimatedObject::step(){

    if(_cur_animation >= _animations.size()) return;

    if(_animation_h.isOver()) selectAnimation(_idle_animation);
    else if(_animation_h.next()) {

        auto&& pixmap = _animation_h.pixmap();

        setPixmap(pixmap);
        setOffset(-pixmap.width()/2, -pixmap.height()/2);
    }
}

UIntegerType AnimatedObject::addAnimation(const Animation& animation) {

    _animations.push_back(animation);

    if(_animations.size() == 1) selectAnimation(0);
    else _update();

    return _animations.size() - 1;
}

void AnimatedObject::selectAnimation(UIntegerType n) {

    _cur_animation = n;

    _update();

    _animation_h.start();

    auto&& pixmap = _animation_h.pixmap();

    setPixmap(pixmap);

    if(scene() != nullptr) scene()->update();

    setOffset(-pixmap.width()/2, -pixmap.height()/2);
}

void AnimatedObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

    if(_handler != nullptr) _handler->animatedObjectMouseDoubleClickEvent(event);
}

void AnimatedObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

    if(_handler != nullptr) _handler->animatedObjectMouseMoveEvent(event);
}

void AnimatedObject::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    if(_handler != nullptr) _handler->animatedObjectMousePressEvent(event);
}

void AnimatedObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

    if(_handler != nullptr) _handler->animatedObjectMouseReleaseEvent(event);
}
