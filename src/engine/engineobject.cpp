
#include <functional>

#include "enginemap.h"
#include "engineobject.h"

EngineObject::~EngineObject() {

    _map->removeObject(this);
    _notifyAll(&Observer::engineObjectDestroyed);
}

bool EngineObject::attachObserver(Observer *h) {

    if(std::find(_observers.begin(), _observers.end(), h) == _observers.end()) {

        _observers.push_back(h);

        return true;
    }

    return false;
}

bool EngineObject::detachObserver(Observer *h) {

    auto it = std::find(_observers.begin(), _observers.end(), h);
    if(it != _observers.end()) {

        *it = _observers.back();
        _observers.pop_back();

        return true;
    }

    return false;
}

bool EngineObject::setPos(PointType p) {

    if(!_map->engineObjectMoveVerify(this, p)) return false;

    _notifyAll(&Observer::engineObjectMoved);

    Base::setPos(p);

    return true;
}

bool EngineObject::setAngle(AngleType angle){

    Base::setAngle(angle);

    _notifyAll(&Observer::engineObjectRotated);

    return true;
}
