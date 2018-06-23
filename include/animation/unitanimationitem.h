
#ifndef UNITANIMATIONITEM_H
#define UNITANIMATIONITEM_H

#include <QGraphicsScene>

#include "config/types.h"
#include "engine/unit.h"

class UnitAnimationItem : public Unit::Handler {

public:

    UnitAnimationItem(const Unit *u) : _scene(nullptr), _unit(u) { u->attachHandler(this); }
    ~UnitAnimationItem() { if(_unit) _unit->detachHandler(this); }

    virtual void redraw() = 0;
    void setScene(QGraphicsScene *scene) {
        if(!_scene) this->removeFromScene(); _scene = scene;
        if(scene) this->addToScene(_scene);
    }
    void clearScene() { setScene(nullptr); }
    QGraphicsScene *scene() const { return _scene; }

protected:

    virtual addToScene(QGraphicsScene *) = 0;
    virtual removeFromScene() = 0;

    virtual unitHandlerObjectDestroyed(Unit *) { _unit = nullptr; }

private:

    QGraphicsScene *_scene;
    const Unit *_unit;
};

#endif // UNITANIMATIONITEM_H
