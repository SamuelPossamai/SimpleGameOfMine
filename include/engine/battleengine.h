
#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include "traits.h"
#include "map.h"

class BattleEngine {

public:

    BattleEngine() : _map(800, 400) {}

    ~BattleEngine();

    void addUnit(const UnitInfo *unit_info, UIntegerType team);

    void step() { _map.step(); }

    void setScene(QGraphicsScene *scene) { _map.setScene(scene); }
    QGraphicsScene *scene() const { return _map.scene(); }

    void placeUnits() { _map.placeUnits(); }

private:

    Map _map;
};

#endif // BATTLEENGINE_H
