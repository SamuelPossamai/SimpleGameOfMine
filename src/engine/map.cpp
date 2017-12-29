
#include "map.h"
#include "unit.h"

#define square(x) ((x)*(x))

void Map::unitsInRange(UnitsVector& vector, PointType p, PositionType range) {

    range *= range;

    for(auto *unit : _units) {

        if((square(unit->x() - p.x) + square(unit->y() - p.y)) <= range) vector.push_back(unit);
    }
}

void Map::addUnit(Unit *unit) {

    if(_scene != nullptr) _scene->addItem(unit);
    _units.push_back(unit);
}

void Map::setScene(QGraphicsScene *scene) {

    for(auto *unit : _units) {

        if(_scene != nullptr) _scene->removeItem(unit);
        if(scene != nullptr) scene->addItem(unit);
    }
    _scene = scene;
}

constexpr bool Map::_using_radians() {

    return Traits<Map>::angle_unit == Traits<Map>::AngleUnitType::radians;
}
