
#include <QPainter>

#include "animation.h"

bool Animation::next() {

    if(isOver()) return false;

    _cur_step++;

    if(isOver()){

        if(_restart) {

            start();

            return true;
        }

        _over_procedure();

        return false;
    }

    _choose_item();

    return true;
}

void Animation::addItem(QGraphicsItem *item, UIntegerType initial_step) {

    if(!isOver()) forceOver();

    item->hide();

    _map[initial_step] = item;
}

void Animation::start() {

    _cur_step = 0;
    _map_it = _map.begin();

    if(_handler != nullptr) _handler->animationStart();

    if(_map_it == _map.end()) return forceOver();

    _choose_item();
}

void Animation::forceOver() {

    _cur_step = _steps;

    _over_procedure();
}

void Animation::setSteps(UIntegerType steps) {

    if(!isOver()) _cur_step = steps;
    _steps = steps;
}

void Animation::_choose_item() {

    while(1){

        if(_map_it == _map.end()) return;

        if(_cur_step != _map_it->first) return;

        if(_item != nullptr) _item->hide();

        _item = _map_it->second;

        _map_it++;

        _item->show();

        _cur_step++;
    }
}
