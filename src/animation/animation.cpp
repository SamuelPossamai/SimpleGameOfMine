
#include <QPainter>
#include <QGraphicsScene>

#include "animation.h"

Animation::Animation(UIntegerType steps, bool restart) : _cur_step(steps), _steps(steps), _restart(restart) {
}

bool Animation::next() {

    if(isOver()) return false;

    _cur_step++;

    if(isOver()){

        if(_restart) start();

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

void Animation::start() {

    _cur_step = 0;
    _vec_pos = 0;

    if(_vec_pos >= _vector.size()) return forceOver();

    _choose_item();
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

        if(isOver()) return changed;

        if(_cur_step != _vector[_vec_pos].second) return changed;

        _vec_pos++;

        changed = true;
    }
}

