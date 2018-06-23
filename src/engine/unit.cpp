
#include "unit.h"
#include "map.h"

Unit::~Unit() {

    _notifyAll(&Handler::unitHandlerObjectDestroyed);
}

bool Unit::receiveDamage(AttackType damage) {

    HealthType new_health_value = health() - damage;

    if(new_health_value >= health()) return true;

    setHealth(new_health_value);

    if(isDead()) {

        _notifyAll(&Handler::unitHandlerDeathEvent);

        return false;
    }

    _notifyAll(&Handler::unitHandlerReceivedDamage);

    return true;
}

void Unit::detachHandler(Handler *h) {

    auto it = std::find(_handlers.begin(), _handlers.end(), h);
    if(it != _handlers.end()) *it = *_handlers.end();
    _handlers.pop_back();
}

bool Unit::setPos(PointType p) {

    if(!_map->unitMoveVerify(this, p)) return false;

    Base::setPos(p);

    _notifyAll(&Handler::unitHandlerMoved);

    return true;
}

bool Unit::setAngle(AngleType angle){

    Base::setAngle(angle);

    _notifyAll(&Handler::unitHandlerRotated);

    return true;
}

std::pair<UIntegerType, Unit::AngleType> Unit::choose() {

    UIntegerType skill = _controller->chooseSkill(this, _map, _interface);
    AngleType angle = unitInfo()->skillNeedAngle(skill) ? _controller->chooseAngle(this, _map, _interface) : 0;

    _notifyAll(&Handler::unitHandlerSkillStarted, skill);

    return { skill, angle };
}
