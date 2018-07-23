
#include "unit.h"
#include "map.h"
#include "uniteffect.h"

Unit::Unit(const UnitInfo *info, UnitController *controller, Map *m, UIntegerType team, BattleWidget *i) :
    Base(info), _team(team), _controller(controller), _map(m),
    _skill(info->skills()), _interface(i) {

}

Unit::~Unit() {

    _notifyAll(&Observer::unitObjectDestroyed);
}

bool Unit::receiveDamage(AttackType damage, Unit *attacking /* = nullptr */) {

    if(attacking) for(auto p : attacking->_effects) damage = p.first->doAttackEffect(attacking, this, damage);
    for(auto p : _effects) damage = p.first->doDefenseEffect(this, attacking, damage);

    if(damage > health()) damage = health();
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

void Unit::healed(HealthType amount, Unit *healing /* = nullptr */) {

    Q_UNUSED(healing);

    HealthType new_health_value = health() + amount;

    if(new_health_value <= health()) return;

    setHealth(new_health_value);

    _notifyAll(&Observer::unitHealed);
}

bool Unit::attachObserver(Observer *h) {

    if(std::find(_observers.begin(), _observers.end(), h) == _observers.end()) {

        _observers.push_back(h);

        return true;
    }

    return false;
}

bool Unit::detachObserver(Observer *h) {

    auto it = std::find(_observers.begin(), _observers.end(), h);
    if(it != _observers.end()) {

        *it = _observers.back();
        _observers.pop_back();

        return true;
    }

    return false;
}

bool Unit::addEffect(const UnitEffect *effect, UIntegerType duration, bool renew /* = false */) {

    _effects.emplace_back(effect, EffectInfo{ duration, renew ? duration : 0 });

    return true;
}

bool Unit::removeEffect(const UnitEffect *effect) {

    auto it = std::find_if(_effects.begin(), _effects.end(),
                           [effect](const EffectsList::value_type& p) { return p.first == effect; } );

    if(it != _effects.end()) {

        *it = _effects.back();
        _effects.pop_back();

        return true;
    }

    return false;
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

    while (!_choose_internal(i));

    _notifyAll(&Observer::unitSkillStarted);

    return true;
}

bool Unit::act() {

    if(isPerformingSkill()) return perform();

    return choose();
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

    for(auto& p : _effects) p.first->doTurnEffect(this, p.second.duration - 1);
    _verify_effects();

    return true;
}

void Unit::select() {

    _notifyAll(&Observer::unitSelected);
}

void Unit::unselect() {

    _notifyAll(&Observer::unitUnselected);
}

bool Unit::_choose_internal(BattleWidget::InputInterface& i) {

    _skill = _controller->chooseSkill(this, _map, i.get());
    if(!isPerformingSkill()) return false;

    _skill_angle = 0;

    if(unitInfo()->skillNeedAngle(_skill)) {

        auto opt = _controller->chooseAngle(this, _map, i.get());
        if(!opt) return false;

        _skill_angle = *opt;
    }

    _skill_step = 0;
    _skill_next_call = 0;

    return true;
}

void Unit::_verify_effects() {

    for(auto it = _effects.begin(); it != _effects.end(); it++) {

        auto& duration = it->second.duration;
        auto& starting_duration = it->second.starting_duration;
        bool renew = starting_duration != 0;

        if(--duration == 0) {

            if(renew){

                duration = starting_duration;
                continue;
            }

            bool is_last = ( it == _effects.end() - 1 );

            if(!is_last) *it = _effects.back();

            _effects.pop_back();

            if(is_last) break;
        }
    }
}
