
#include "animationhandler.h"

std::mt19937 AnimationHandler::_gen((std::random_device())());

#include <iostream>

void AnimationHandler::start(bool rnd_start) {

    _cur_step = 0;
    _vec_pos = 0;

    if(_animation->images() == 0) return forceOver();

    _choose_item();

    if(rnd_start && _animation->getFlag(Animation::Flag::RandomStart) && _animation->steps() > 0){

        std::uniform_int_distribution<UIntegerType> rnd(0, _animation->steps() - 1);

        UIntegerType n = rnd(_gen);

        for(UIntegerType i = 0; i < n; i++) next();
    }
}

bool AnimationHandler::next() {

    if(isOver()) return false;

    _cur_step++;

    if(isOver()){

        if(_animation->cyclic()) restart();

        return true;
    }

    return _choose_item();
}

void AnimationHandler::forceOver() {

    _cur_step = _animation->steps();
}

QPixmap AnimationHandler::pixmap() const {

    if(_vec_pos == 0 || _vec_pos > _animation->images()) return QPixmap();

    return _animation->pixmap(_vec_pos - 1);
}

bool AnimationHandler::_choose_item() {

    bool changed = false;

    while(1){

        if(isOver() || (_vec_pos) >= _animation->images()) return changed;

        if(_cur_step != _animation->startingStep(_vec_pos)) return changed;

        _vec_pos++;

        changed = true;
    }
}

