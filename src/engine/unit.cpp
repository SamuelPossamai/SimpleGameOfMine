
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

bool Unit::choose() {

    _skill = _controller->chooseSkill(this, _map, _interface);
    if(!isPerformingSkill()) return false;

    _skill_angle = unitInfo()->skillNeedAngle(_skill) ? _controller->chooseAngle(this, _map, _interface) : 0;
    _skill_step = 0;
    _skill_next_call = 0;

    _notifyAll(&Handler::unitHandlerSkillStarted);

    return true;
}

bool Unit::perform() {

    if(_skill_step == 0) {

        startSkillAnimation(_skill);

        removeSelectEffect();
    }

    if(_skill_next_call == _skill_step){

        _skill_next_call = _skill_step + unitInfo()->callSkill(_skill, this, _map, { _skill_step, _skill_angle });

        if(_skill_next_call <= _skill_step) {

            endSkillAnimation();
            _skill = unitInfo()->skills();

            _notifyAll(&Unit::Handler::unitHandlerSkillFinished);

            return false;
        }
    }

    _skill_step++;

    return true;
}


