
#include <cmath>

#include "map.h"
#include "unit.h"
#include "engineobject.h"

template<typename T>
constexpr T square(T x) { return x * x; }

template<typename T>
constexpr T abs(T x) { return (x >= 0) ? x : -x; }

Map::EngineObjectsVector Map::objectsInRange(PointType p, PositionType range) {

    EngineObjectsVector v;

    objectsInRange(v, p, range);

    return v;
}

Map::UnitsVector Map::unitsInRange(PointType p, PositionType range) {

    UnitsVector v;

    unitsInRange(v, p, range);

    return v;
}

Map::EngineObjectsVector Map::objectsInRange(PointType p, PositionType range, AngleType angle, AngleType region_angle) {

    EngineObjectsVector v;

    objectsInRange(v, p, range, angle, region_angle);

    return v;
}

void Map::objectsInRange(EngineObjectsVector& vector, PointType p, PositionType range) {

    _in_range_base(_objects, vector, p, range);
}

void Map::unitsInRange(UnitsVector& vector, PointType p, PositionType range) {

    _in_range_base(_units, vector, p, range);
}

void Map::objectsInRange(EngineObjectsVector& vector, PointType p, PositionType range, AngleType angle, AngleType region_angle) {

    if(region_angle >= 2*M_PI) return objectsInRange(vector, p, range);
    if(region_angle == 0) return objectsInLine(vector, p, range, angle);

    range *= range;

    for(auto object : _objects) {

        auto vet_x = RealType(object->x()) - p.x;
        auto vet_y = RealType(object->y()) - p.y;
        auto squared_distance = square(vet_x) + square(vet_y);

        if(squared_distance <= PositionType(range + square(object->size()))) {

            AngleType object_angle = std::atan2(vet_y, vet_x);
            AngleType object_region = std::atan2(object->size(), std::sqrt(squared_distance));

            if(_inside_region(angle, region_angle, object_angle, object_region)) vector.push_back(object);
        }
    }
}

void Map::objectsInLine(EngineObjectsVector& vector, PointType p, PositionType range, AngleType angle) {

    (void) vector;
    (void) p;
    (void) range;
    (void) angle;
}

Unit *Map::closerEnemy(const Unit *u) {

    Unit *closer = nullptr;
    RealType closer_sqr_dist = 0;

    for(auto unit : _units) {

        if(unit == nullptr) continue;

        if(unit->team() == u->team()) continue;

        auto cur_squared_distance = _objects_squared_distance(unit, u);

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


void Map::addObject(EngineObject *object) {

    Unit *unit = dynamic_cast<Unit *>(object);

    if(unit) addUnit(unit);
    else addObjectNotUnit(object);
}

void Map::addUnit(Unit *unit) {

    addObjectNotUnit(unit);
    _units.push_back(unit);
}

void Map::removeObject(EngineObject *object) {

    _remove_from_vector(_objects, object);
    _remove_from_vector(_units, static_cast<Unit *>(object));
}

bool Map::engineObjectMoveVerify(EngineObject *obj, const PointType& p) {

    if(Traits<Map>::solid_border && (p.x < PointType::CoordType(obj->size()) ||
                                     p.x + PointType::CoordType(obj->size()) > _width ||
                                     p.y < PointType::CoordType(obj->size()) ||
                                     p.y + PointType::CoordType(obj->size()) > _height)) return false;

    return true;
}

void Map::placeUnits(){

    if(unitsNumber() == 0) return;

    UIntegerType nmax_teams[2] = {};
    for(UIntegerType i = 0; i < unitsNumber(); i++) nmax_teams[unitAccess(i)->team()]++;

    UIntegerType n_teams[2] = {};
    for(UIntegerType i = 0; i < unitsNumber(); i++) {

        Unit *unit = unitAccess(i);

        UIntegerType x = unit->team() ? _width - 50 : 50;
        UIntegerType y = _height*RealType(++n_teams[unit->team()])/(nmax_teams[unit->team()] + 1);

        unit->setPos(x, y);
        unit->setAngle(unit->team() ? M_PI : 0);
    }
}

RealType Map::objectsDistance(const EngineObject *u1, const EngineObject *u2) {

    return std::sqrt(_objects_squared_distance(u1, u2));
}

RealType Map::_objects_squared_distance(const EngineObject *u1, const EngineObject *u2) {

    auto vet_x = RealType(u1->x()) - u2->x();
    auto vet_y = RealType(u1->y()) - u2->y();

    return square(vet_x) + square(vet_y);
}

bool Map::_inside_region(AngleType a1, AngleType r1, AngleType a2, AngleType r2) {

    if(abs(a1 - a2) < r1 + r2) return true;
    if(360 - abs(a1 - a2) < (r1 + r2)) return true;

    return false;
}

template<typename T>
void Map::_in_range_base(std::vector<T *>& src, std::vector<T *>& dest, PointType p, PositionType range) {

    range *= range;

    for(auto obj : src) {

        auto x_dis = square(RealType(obj->x()) - p.x);
        auto y_dis = square(RealType(obj->y()) - p.y);

        if((x_dis + y_dis) <= RealType(range + square(obj->size()))) dest.push_back(obj);
    }
}

template<typename T>
bool Map::_remove_from_vector(std::vector<T *>& v, T *obj) {

    auto it = std::find(v.begin(), v.end(), obj);

    if(it == v.end()) return false;

    *it = v.back();
    v.pop_back();

    return true;
}
