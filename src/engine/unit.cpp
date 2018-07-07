
#include "unit.h"
#include "map.h"
#include "unitanimations/basicunitgraphicitem.h"

Unit::Unit(const UnitInfo *info, UnitController *controller, Map *m, UIntegerType team, BattleWidget *i) :
    Base(info), _team(team), _controller(controller), _map(m),
    _skill(info->skills()), _interface(i) {

}

Unit::~Unit() {

    _notifyAll(&Observer::unitObjectDestroyed);
}

bool Unit::receiveDamage(AttackType damage) {

    HealthType new_health_value = health() - damage;

    if(new_health_value >= health()) return true;

    setHealth(new_health_value);

    if(isDead()) {

        _notifyAll(&Observer::unitDeathEvent);

        return false;
    }

    _notifyAll(&Observer::unitReceivedDamage);

    return true;
}

void Unit::detachObserver(Observer *h) {

    auto it = std::find(_observers.begin(), _observers.end(), h);
    if(it != _observers.end()) *it = *_observers.end();
    _observers.pop_back();
}

bool Unit::setPos(PointType p) {

    if(!_map->unitMoveVerify(this, p)) return false;

    Base::setPos(p);

    _notifyAll(&Observer::unitMoved);

    return true;
}

bool Unit::setAngle(AngleType angle){

    Base::setAngle(angle);

    _notifyAll(&Observer::unitRotated);

    return true;
}

bool Unit::choose() {

    auto i = _interface->inputInterface();

    _skill = _controller->chooseSkill(this, _map, i.get());
    if(!isPerformingSkill()) return false;

    _skill_angle = unitInfo()->skillNeedAngle(_skill) ? _controller->chooseAngle(this, _map, i.get()) : 0;
    _skill_step = 0;
    _skill_next_call = 0;

    _notifyAll(&Observer::unitSkillStarted);

    return true;
}

bool Unit::perform() {

    if(_skill_next_call == _skill_step){

        _skill_next_call = _skill_step + unitInfo()->callSkill(_skill, this, _map, { _skill_step, _skill_angle });

        if(_skill_next_call <= _skill_step) {

            _skill = unitInfo()->skills();

            _notifyAll(&Unit::Observer::unitSkillFinished);

            return false;
        }
    }

    _skill_step++;
    _notifyAll(&Unit::Observer::unitSkillAdvance);

    return true;
}

void Unit::select() {

    _notifyAll(&Observer::unitSelected);
}

void Unit::unselect() {

    _notifyAll(&Observer::unitUnselected);
}
