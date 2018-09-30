
#include "unit.h"
#include "map.h"
#include "uniteffect.h"

Unit::Unit(const UnitInfo *info, UnitController *controller, Map *m, UIntegerType team, BattleWidget *i) :
    Base(info, m), _team(team), _controller(controller), _skill(info->skills()), _interface(i) {

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

bool Unit::consumeEnergy(EnergyType energy) {

    if(energy > this->energy()) return false;

    this->setEnergy(this->energy() - energy);

    _notifyAll(&Observer::unitEnergyConsumed);

    return true;
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

    _notifyAll(&Observer::unitEffectAdded, effect);

    _effects.emplace_back(effect, EffectInfo{ duration, duration, renew });

    return true;
}

bool Unit::removeEffect(const UnitEffect *effect) {

    auto it = std::find_if(_effects.begin(), _effects.end(),
                           [effect](const EffectsList::value_type& p) { return p.first == effect; } );

    if(it != _effects.end()) {

        _notifyAll(&Observer::unitEffectRemoved, it->first);

        *it = _effects.back();
        _effects.pop_back();

        return true;
    }

    return false;
}

bool Unit::setPos(PointType p) {

    bool v = Base::setPos(p);

    _notifyAll(&Observer::unitMoved);

    return v;
}

bool Unit::setAngle(AngleType angle){

    bool v = Base::setAngle(angle);

    _notifyAll(&Observer::unitRotated);

    return v;
}

bool Unit::choose() {

    auto i = _interface->inputInterface();

    while (!_choose_internal(i));

    _notifyAll(&Observer::unitSkillStarted);

    return true;
}

bool Unit::act() {

    if(isDead()) return false;

    if(isPerformingSkill()) perform();
    else choose();

    return true;
}

bool Unit::perform() {

    if(_skill_next_call == _skill_step){

        _skill_next_call = _skill_step + unitInfo()->callSkill(_skill, this, map(), { _skill_step, _skill_angle });

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

Unit::PointType Unit::maxPosition() const {

    if(map()->width() < size() || map()->height() < size()) return { 0, 0 };

    return { map()->width() - size(), map()->height() - size()};
}

Unit::SpeedType Unit::effectiveSpeed() const {

    SpeedType s = baseSpeed();

    for(auto p : _effects) s = p.first->doSpeedEffect(this, s);

    return s;
}

bool Unit::_choose_internal(BattleWidget::InputInterface& i) {

    _skill = _controller->chooseSkill(this, map(), i.get());
    if(!isPerformingSkill()) return false;

    _skill_angle = 0;

    if(unitInfo()->skillNeedAngle(_skill)) {

        auto opt = _controller->chooseAngle(this, map(), i.get());
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
        bool renew = it->second.renew;

        if(--duration == 0) {

            if(renew){

                duration = starting_duration;
                continue;
            }

            _notifyAll(&Observer::unitEffectRemoved, it->first);

            bool is_last = ( it == _effects.end() - 1 );

            if(!is_last) *it = _effects.back();

            _effects.pop_back();

            if(is_last) break;
        }
    }
}
