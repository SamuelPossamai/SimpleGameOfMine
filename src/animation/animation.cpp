
#include <QPainter>
#include <QGraphicsScene>

#include "animation.h"

std::mt19937 Animation::_gen((std::random_device())());

Animation::Animation(UIntegerType steps, bool restart) : _cur_step(steps), _steps(steps), _restart(restart) {
}

bool Animation::next() {

    if(isOver()) return false;

    _cur_step++;

    if(isOver()){

        if(_restart) restart();

        return true;
    }

    return _choose_item();
}

void Animation::addImage(const QPixmap& p, UIntegerType initial_step) {

    if(!isOver()) forceOver();

    if(!_vector.empty()) {

        if(initial_step < _vector.back().second) {

            for(auto it = _vector.begin(); it != _vector.end(); it++){

                if(initial_step >= it->second) {

                    _vector.emplace(it, p, initial_step);

                    return;
                }
            }
        }
    }

    _vector.emplace_back(p, initial_step);

}

void Animation::start(bool rnd_start) {

    _cur_step = 0;
    _vec_pos = 0;

    if(_vector.empty()) return forceOver();

    _choose_item();

    if(rnd_start && getFlag(Flag::RandomStart) && steps() > 0){


        std::uniform_int_distribution<UIntegerType> rnd(0, steps() - 1);

        UIntegerType n = rnd(_gen);

        for(UIntegerType i = 0; i < n; i++) next();
    }
}

void Animation::forceOver() {

    _cur_step = _steps;
}

void Animation::setSteps(UIntegerType steps) {

    if(!isOver()) _cur_step = steps;
    _steps = steps;
}

bool Animation::_choose_item() {

    bool changed = false;

    while(1){

        if(isOver() || (_vec_pos) >= _vector.size()) return changed;

        if(_cur_step != _vector[_vec_pos].second) return changed;

        _vec_pos++;

        changed = true;
    }
}

