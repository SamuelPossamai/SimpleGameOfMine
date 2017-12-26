
#include <QPainter>
#include <QGraphicsScene>

#include "animation.h"

Animation::Animation(QGraphicsScene *scene, UIntegerType steps, bool restart) :
    _scene(scene), _cur_step(steps), _steps(steps), _restart(restart), _item(new QGraphicsPixmapItem), _obj(nullptr) {

    if(scene != nullptr) scene->addItem(_item);

    _item->hide();
}

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

void Animation::addImage(const QPixmap& p, UIntegerType initial_step) {

    if(!isOver()) forceOver();

    _map[initial_step] = p;
}

void Animation::start() {

    _cur_step = 0;
    _map_it = _map.begin();

    if(_map_it == _map.end()) return forceOver();

    _item->show();

    _choose_item();

    update();
}

void Animation::forceOver() {

    _cur_step = _steps;

    _over_procedure();
}

void Animation::setScene(QGraphicsScene *scene) {

    if(_scene != nullptr) _scene->removeItem(_item);
    if(scene != nullptr) scene->addItem(_item);

    _scene = scene;
}

void Animation::setSteps(UIntegerType steps) {

    if(!isOver()) _cur_step = steps;
    _steps = steps;
}

void Animation::update() {

    if(!_item) return;

    if(_obj){

        auto half_width = _item->pixmap().width()/2;
        auto half_height = _item->pixmap().height()/2;

        _item->setRotation(_obj->angle());
        _item->setOffset(-half_width, -half_height);
        _item->setPos(_obj->x(), _obj->y());

    }else{

        _item->setRotation(0);
        _item->setOffset(0, 0);
        _item->setPos(0, 0);
    }
}

void Animation::_over_procedure() {

    _item->hide();
}

void Animation::_choose_item() {

    while(1){

        if(_map_it == _map.end()) return;

        if(_cur_step != _map_it->first) return;

        _item_change(_map_it->second);

        _map_it++;
        _cur_step++;
    }
}

void Animation::_item_change(const QPixmap& new_pixmap) {

    _item->setPixmap(new_pixmap);

    update();
}

