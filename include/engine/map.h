#ifndef MAP_H
#define MAP_H

#include <vector>

#include <QGraphicsScene>

#include "engine_traits.h"

class Map {

public:

    using PointType = Traits<Map>::PointType;
    using PositionType = Traits<Map>::PositionType;
    using AngleType = Traits<Map>::AngleType;
    using UnitsVector = std::vector<Unit *>;
    using ConstUnitsVector = std::vector<const Unit *>;

    Map(PositionType width, PositionType height) : _width(width), _height(height), _scene(nullptr) {}

    void addUnit(Unit *unit);
    void removeUnit(Unit *unit);

    void step();

    UnitsVector unitsInRange(PointType p, PositionType range);
    UnitsVector unitsInRange(PointType p, PositionType range, AngleType angle, AngleType region_angle);
    UnitsVector unitsInLine(PointType p, PositionType range, AngleType angle);

    void unitsInRange(UnitsVector& vector, PointType p, PositionType range);
    void unitsInRange(UnitsVector& vector, PointType p, PositionType range, AngleType angle, AngleType region_angle);
    void unitsInLine(UnitsVector& vector, PointType p, PositionType range, AngleType angle);

    Unit *closerEnemy(const Unit *);
    const Unit *closerEnemy(const Unit *u) const { return const_cast<Map *>(this)->closerEnemy(u); }

    Unit *unitAccess(UIntegerType n) { return _units[n]; }
    const Unit *unitAccess(UIntegerType n) const { return _units[n]; }

    UIntegerType units() const { return _units.size(); }

    void setScene(QGraphicsScene *scene);
    QGraphicsScene *scene() const { return _scene; }

    bool setUnitPosition(Unit *, const PointType&);

    void placeUnits();

    static RealType unitsDistance(const Unit *, const Unit *);

private:

    static RealType _units_squared_distance(const Unit *, const Unit *);
    static constexpr bool _using_radians() { return Traits<Map>::angle_unit == Traits<Map>::AngleUnitType::radians; }

    static bool _inside_region(AngleType a1, AngleType r1, AngleType a2, AngleType r2);

    PositionType _width, _height;

    UnitsVector _units;

    QGraphicsScene *_scene;
};

#endif // MAP_H
