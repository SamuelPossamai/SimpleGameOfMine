#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>

#include "traits.h"

class Map {

public:

    using PointType = Traits<Map>::PointType;
    using PositionType = Traits<Map>::PositionType;
    using AngleType = Traits<Map>::AngleType;
    using UnitsVector = std::vector<Unit *>;

    Map(PositionType width, PositionType height) : _width(width), _height(height), _scene(nullptr) {}

    void addUnit(Unit *unit);

    void removeUnit(Unit *unit);

    UnitsVector unitsInRange(PointType p, PositionType range);
    UnitsVector unitsInRange(PointType p, PositionType range, AngleType angle, AngleType region_angle);

    void unitsInRange(UnitsVector& vector, PointType p, PositionType range);
    void unitsInRange(UnitsVector& vector, PointType p, PositionType range, AngleType angle, AngleType region_angle);

    void setScene(QGraphicsScene *scene);
    QGraphicsScene *scene() const { return _scene; }

private:

    constexpr bool _using_radians();

    PositionType _width, _height;

    std::vector<Unit *> _units;

    QGraphicsScene *_scene;
};

#endif // MAP_H
