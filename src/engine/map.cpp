
#include <cmath>

#include "map.h"
#include "unit.h"

template<typename T>
constexpr T square(T x) { return x * x; }

template<typename T>
constexpr T abs(T x) { return (x >= 0) ? x : -x; }

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

    for(auto unit : _units) {

        auto x_dis = square(RealType(unit->x()) - p.x);
        auto y_dis = square(RealType(unit->y()) - p.y);

        if((x_dis + y_dis) <= RealType(range + square(unit->size()))) vector.push_back(unit);
    }
}

void Map::unitsInRange(UnitsVector& vector, PointType p, PositionType range, AngleType angle, AngleType region_angle) {

    if(region_angle >= _using_radians() ? 2*M_PI : 360) return unitsInRange(vector, p, range);
    if(region_angle == 0) return unitsInLine(vector, p, range, angle);

    range *= range;

    for(auto unit : _units) {

        auto vet_x = RealType(unit->x()) - p.x;
        auto vet_y = RealType(unit->y()) - p.y;
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

Unit *Map::closerEnemy(const Unit *u) {

    Unit *closer = nullptr;
    RealType closer_sqr_dist = 0;

    for(auto unit : _units) {

        if(unit->team() == u->team()) continue;

        auto cur_squared_distance = _units_squared_distance(unit, u);

        if(closer == nullptr || closer_sqr_dist > cur_squared_distance) {

            closer_sqr_dist = cur_squared_distance;
            closer = unit;
        }
    }

    return closer;
}

bool Map::gameEndVerify() const {

    if(_units.empty()) return true;

    UIntegerType first_team = _units[0]->team();

    for(Unit *unit : _units) if(unit->team() != first_team) return false;

    return true;
}

void Map::addUnit(Unit *unit) {

    if(_scene != nullptr) unit->setScene(_scene);
    _units.push_back(unit);
}

void Map::removeUnit(Unit *unit) {

     *std::find(_units.begin(), _units.end(), unit) = _units.back();

    _units.pop_back();
}

void Map::setScene(QGraphicsScene *scene) {

    for(auto unit : _units) unit->setScene(scene);

    _scene = scene;
}

bool Map::unitMoveVerify(Unit *u, const PointType& p) {

    if(Traits<Map>::solid_border && (p.x < PointType::CoordType(u->size()) ||
                                     p.x + PointType::CoordType(u->size()) > _width ||
                                     p.y < PointType::CoordType(u->size()) ||
                                     p.y + PointType::CoordType(u->size()) > _height)) return false;

    return true;
}

void Map::placeUnits(){

    if(units() == 0) return;

    UIntegerType team_0 = 0, team_1 = 0;

    for(UIntegerType i = 0; i < units(); i++) {

        UIntegerType n = team_0;

        Unit *unit = unitAccess(i);

        if(unit->team() == 1) n = team_1++;
        else team_0++;

        unit->setPos((unit->team() ? _width - 50 : 50), (_height/4 + (_height/2)*(RealType(n + 1)/(units() + 1))));
        unit->setAngle(unit->team() ? M_PI : 0);
    }
}

RealType Map::unitsDistance(const Unit *u1, const Unit *u2) {

    return std::sqrt(_units_squared_distance(u1, u2));
}

RealType Map::_units_squared_distance(const Unit *u1, const Unit *u2) {

    auto vet_x = RealType(u1->x()) - u2->x();
    auto vet_y = RealType(u1->y()) - u2->y();

    return square(vet_x) + square(vet_y);
}

bool Map::_inside_region(AngleType a1, AngleType r1, AngleType a2, AngleType r2) {

    if(abs(a1 - a2) < r1 + r2) return true;
    if(360 - abs(a1 - a2) < (r1 + r2)) return true;

    return false;
}
