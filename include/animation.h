#ifndef Animation_H
#define Animation_H

#include <map>

#include <QGraphicsItem>

#include "types.h"

class AnimationHandler {

public:

    virtual void animationOver() {}

    virtual void animationStart() {}

    virtual void animationItemChange(QGraphicsItem *) {}

};

class Animation {

public:

    Animation() : Animation(1) {}

    explicit Animation(UIntegerType steps, bool restart = false) : _handler(nullptr), _cur_step(steps),
        _steps(steps), _restart(restart), _item(nullptr) {}

    explicit Animation(AnimationHandler *handler, UIntegerType steps = 1);

    Animation(const Animation& other);

    bool next();

    bool step() { return next(); }

    void addItem(QGraphicsItem *item, UIntegerType initial_step);

    bool isOver() const { return _cur_step >= _steps; }

    void start();

    void restart() { start(); }

    void forceOver();

    void setSteps(UIntegerType steps);

    UIntegerType steps() const { return _steps; }

    QGraphicsItem *item() { return _item; }

private:

    void _over_procedure(){

        if(_item != nullptr){

            _item->hide();
            _item = nullptr;
        }

        if(_handler != nullptr) _handler->animationOver();
    }

    void _choose_item();

    using MapType = std::map<UIntegerType, QGraphicsItem *>;

    AnimationHandler *_handler;

    MapType _map;

    UIntegerType _cur_step;
    MapType::iterator _map_it;

    UIntegerType _steps;
    bool _restart;

    QGraphicsItem *_item;
};

#endif // Animation_H
