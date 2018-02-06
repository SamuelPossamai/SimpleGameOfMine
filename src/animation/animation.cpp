
#include <QPainter>
#include <QGraphicsScene>

#include "animation.h"

Animation::Animation(UIntegerType steps, bool restart) : _steps(steps), _restart(restart) {
}

void Animation::addImage(const QPixmap& p, UIntegerType initial_step) {

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

void Animation::setSteps(UIntegerType steps) {

    _steps = steps;
}

