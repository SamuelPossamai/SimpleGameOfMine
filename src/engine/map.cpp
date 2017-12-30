
#include <cmath>

#include "map.h"
#include "unit.h"

#define square(x) ((x)*(x))
#define abs(x) ((x >= 0) ? x : -x)

void Map::step() {

    for(auto *unit : _units) unit->step();
}

Map::UnitsVector Map::unitsInRange(PointType p, PositionType range) {

    UnitsVector v;

    unitsInRange(v, p, range);

    return v;
}

Map::UnitsVector Map::unitsInRange(PointType p, PositionType range, AngleType angle, AngleType region_angle) {

    UnitsVector v;

    unitsInRange(v, p, range, angle, region_angle);

    return v;
}

void Map::unitsInRange(UnitsVector& vector, PointType p, PositionType range) {

    range *= range;

    for(auto *unit : _units) {

        if((square(unit->x() - p.x) + square(unit->y() - p.y)) <= PositionType(range + square(unit->size()))) {

            vector.push_back(unit);
        }
    }
}

void Map::unitsInRange(UnitsVector& vector, PointType p, PositionType range, AngleType angle, AngleType region_angle) {

    if(region_angle >= _using_radians() ? 2*M_PI : 360) return unitsInRange(vector, p, range);
    if(region_angle == 0) return unitsInLine(vector, p, range, angle);

    range *= range;

    for(auto *unit : _units) {

        PositionType vet_x = unit->x() - p.x;
        PositionType vet_y = unit->y() - p.y;
        auto squared_distance = square(vet_x) + square(vet_y);

        if(squared_distance <= PositionType(range + square(unit->size()))) {

            const RealType angle_conversion = _using_radians() ? 1 : 180/M_PI;

            AngleType unit_angle = std::atan2(vet_y, vet_x)*angle_conversion;
            AngleType unit_region = std::atan2(unit->size(), std::sqrt(squared_distance))*angle_conversion;

            if(_inside_region(angle, region_angle, unit_angle, unit_region)) vector.push_back(unit);
        }
    }
}

void Map::unitsInLine(UnitsVector& vector, PointType p, PositionType range, AngleType angle) {

    (void) vector;
    (void) p;
    (void) range;
    (void) angle;
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

bool Map::_inside_region(AngleType a1, AngleType r1, AngleType a2, AngleType r2) {

    if(abs(a1 - a2) < r1 + r2) return true;
    if(360 - abs(a1 - a2) < (r1 + r2)) return true;

    return false;
}
