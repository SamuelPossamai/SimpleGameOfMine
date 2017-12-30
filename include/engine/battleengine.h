
#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include "traits.h"
#include "map.h"

class BattleEngine {

public:

    BattleEngine() : _map(1000, 1000) {}

    void addUnit(const UnitInfo *unit_info);
    void addUnit(Unit *unit) { _map.addUnit(unit); } // method for test

    void step() { _map.step(); }

    void setScene(QGraphicsScene *scene) { _map.setScene(scene); }
    QGraphicsScene *scene() const { return _map.scene(); }

private:

    Map _map;
};

#endif // BATTLEENGINE_H
