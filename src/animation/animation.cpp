
#include <utility/imagecolorchange.h>

#include "animation.h"

Animation::Animation(UIntegerType steps, bool restart) : _steps(steps) {

    setIsPeriodic(restart);
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

void Animation::changeColor(const utility::ImageColorChange& icch) {

    for(auto& p : _vector) {

        QPixmap& pixmap = p.first;
        QImage i = pixmap.toImage();
        icch.changeImage(i);
        pixmap = QPixmap::fromImage(i);
    }
}

