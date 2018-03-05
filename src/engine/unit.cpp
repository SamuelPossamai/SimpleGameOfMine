
#include "unit.h"

bool Unit::receiveDamage(AttackType damage) {

    HealthType new_health_value = health() - damage;

    if(new_health_value >= health()) return true;

    setHealth(new_health_value);

    if(isDead()) {

        if(_handler != nullptr) _handler->unitHandlerDeathEvent(this);

        return false;
    }

    return true;
}
