
#include <variant.h>

#include "enginemap.h"
#include "engineobject.h"

EngineObject::~EngineObject() {

    _map->removeObject(this);
}

bool EngineObject::setPos(PointType p) {

    if(!_map->engineObjectMoveVerify(this, p)) return false;

    notify(ObservedEventType::Moved, sutils::Variant());

    Base::setPos(p);

    return true;
}

bool EngineObject::setAngle(AngleType angle){

    Base::setAngle(angle);

    notify(ObservedEventType::Rotated, sutils::Variant());

    return true;
}
