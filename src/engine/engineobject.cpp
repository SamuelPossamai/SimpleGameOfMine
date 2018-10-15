
#include "enginemap.h"
#include "engineobject.h"

bool EngineObject::setPos(PointType p) {

    if(!_map->engineObjectMoveVerify(this, p)) return false;

    Base::setPos(p);

    return true;
}

bool EngineObject::setAngle(AngleType angle){

    Base::setAngle(angle);

    return true;
}
