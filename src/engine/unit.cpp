
#include <iostream>

#include "utility/variant.h"
#include "unit.h"
#include "enginemap.h"
#include "uniteffect.h"
#include "unitskillfactory.h"

#include "gameinfo/skills.h"

Unit::Unit(const UnitInfo *info, UnitController *controller, EngineMap *m, BattleWidget *i,
           const Attributes& attr, UIntegerType level, UIntegerType team, const Character *c) :
    Base(info, m, attr, level), _team(team), _controller(controller), _interface(i), _character(c) {

    auto v = unitInfo()->getSkills(this);

    for(auto&& s: v) {

        auto opt = gameinfo::Skills::get(std::get<0>(s));
        if(!opt) {

            std::cerr << "Failed to load skill '" << std::get<0>(s) << '\'' << std::endl;
            continue;
        }

        UnitSkillFactory *factory = opt->factory;

        UnitSkill *skill = factory->create(std::get<1>(s));

        _skills.push_back({ std::get<0>(s), skill });
    }

    _skill = _skills.size();
}

Unit::~Unit() {

    for(auto&& p : _skills) std::get<1>(p)->destroy();
}

bool Unit::receiveDamage(AttackType damage, Unit *attacking) {

    for(auto p : attacking->_effects) damage = p.first->doAttackEffect(attacking, this, damage);

    return receiveDamage(damage, static_cast<EngineObject *>(attacking));
}

bool Unit::receiveDamage(AttackType damage, EngineObject *attacking /* = nullptr */) {

    for(auto p : _effects) damage = p.first->doDefenseEffect(this, attacking, damage);

    if(damage > health()) damage = health();
    HealthType new_health_value = health() - damage;

    if(new_health_value >= health()) return true;

    setHealth(new_health_value);

    if(isDead()) {

        map()->removeObject(this);
        notify(ObservedEventType::DeathEvent, utility::Variant());

        return false;
    }

    setRage(rage() + damage);

    notify(ObservedEventType::ReceivedDamage, utility::Variant::Integer(damage));

    return true;
}

void Unit::healed(HealthType amount, Unit *healing /* = nullptr */) {

    Q_UNUSED(healing)

    HealthType new_health_value = health() + amount;

    if(new_health_value <= health()) return;

    setHealth(new_health_value);

    notify(ObservedEventType::Healed, utility::Variant::Integer(amount));
}

bool Unit::consumeEnergy(EnergyType energy) {

    if(energy > this->energy()) return false;

    this->setEnergy(this->energy() - energy);

    notify(ObservedEventType::EnergyConsumed, utility::Variant::Integer(energy));

    return true;
}

bool Unit::consumeSpecial(SpecialType special) {

    if(special > this->special()) return false;

    this->setSpecial(this->special() - special);

    return true;
}

bool Unit::consumeRage(RageType rage) {

    if(rage > this->rage()) return false;

    this->setRage(this->rage() - rage);

    return true;
}

bool Unit::addEffect(const UnitEffect *effect, UIntegerType duration, bool renew /* = false */) {

    auto tmp = utility::VariantList({ utility::Variant::Pointer(effect), utility::Variant::Integer(duration), renew });

    notify(ObservedEventType::EffectAdded, std::move(tmp));

    _effects.emplace_back(effect, EffectInfo{ duration, duration, renew });

    return true;
}

bool Unit::removeEffect(const UnitEffect *effect) {

    auto it = std::find_if(_effects.begin(), _effects.end(),
                           [effect](const EffectsList::value_type& p) { return p.first == effect; } );

    if(it != _effects.end()) {

        notify(ObservedEventType::EffectRemoved, utility::Variant::Pointer(it->first));

        *it = _effects.back();
        _effects.pop_back();

        return true;
    }

    return false;
}

bool Unit::choose() {

    auto i = _interface->inputInterface();

    while (!_choose_internal(i));

    notify(ObservedEventType::SkillStarted, utility::Variant());

    return true;
}

bool Unit::act() {

    if(isDead()) return false;

    if(isPerformingSkill()) perform();
    else choose();

    return true;
}

bool Unit::perform() {

    UnitSkill::ProjectileCreationInterface pci(_interface);

    if(_skill_next_call == _skill_step){

        _skill_next_call = _skill_step + _skills.at(_skill).second->action(this, map(), pci, { _skill_step, _skill_angle });

        if(_skill_next_call <= _skill_step) {

            _skill = skillsAmount();

            notify(ObservedEventType::SkillFinished, utility::Variant());

            return false;
        }
    }

    _skill_step++;
    notify(ObservedEventType::SkillAdvance, utility::Variant());

    for(auto& p : _effects) p.first->doTurnEffect(this, p.second.duration - 1);
    _verify_effects();

    return true;
}

void Unit::select() {

    notify(ObservedEventType::Selected, utility::Variant());
}

void Unit::unselect() {

    notify(ObservedEventType::Unselected, utility::Variant());
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

    if(_skills.at(_skill).second->needAngle()) {

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

            notify(ObservedEventType::EffectRemoved, utility::Variant::Pointer(it->first));

            bool is_last = ( it == _effects.end() - 1 );

            if(!is_last) *it = _effects.back();

            _effects.pop_back();

            if(is_last) break;
        }
    }
}

bool Unit::setSpecial(SpecialType val) {

    if(UnitBase::setSpecial(val)) {

        notify(ObservedEventType::SpecialChanged, utility::Variant());
        return true;
    }
    return false;
}

bool Unit::setRage(RageType val) {

    if(UnitBase::setRage(val)) {

        notify(ObservedEventType::RageChanged, utility::Variant());
        return true;
    }
    return false;
}

void Unit::ObserverWrapper::update(const EngineObject *o, UIntegerType event_type, const utility::Variant& v) {

    const Unit *u = static_cast<const Unit *>(o);

    switch(event_type) {

        case Unit::ObservedEventType::SkillStarted:
            this->unitSkillStarted(u);
            break;
        case Unit::ObservedEventType::SkillAdvance:
            this->unitSkillAdvance(u);
            break;
        case Unit::ObservedEventType::SkillFinished:
            this->unitSkillFinished(u);
            break;
        case Unit::ObservedEventType::ReceivedDamage:
            this->unitReceivedDamage(u);
            break;
        case Unit::ObservedEventType::Healed:
            this->unitHealed(u);
            break;
        case Unit::ObservedEventType::DeathEvent:
            this->unitDeathEvent(u);
            break;
        case Unit::ObservedEventType::Selected:
            this->unitSelected(u);
            break;
        case Unit::ObservedEventType::Unselected:
            this->unitUnselected(u);
            break;
        case Unit::ObservedEventType::EnergyConsumed:
            this->unitEnergyConsumed(u);
            break;
        case Unit::ObservedEventType::SpecialChanged:
            this->unitSpecialChanged(u);
            break;
        case Unit::ObservedEventType::RageChanged:
            this->unitRageChanged(u);
            break;
        case Unit::ObservedEventType::EffectAdded: {

            auto& l = v.get<utility::Variant::List>();
            this->unitEffectAdded(u, static_cast<const UnitEffect *>(l.at(0).get<utility::Variant::Pointer>()));
            break;
        }
        case Unit::ObservedEventType::EffectRemoved:
            this->unitEffectRemoved(u, static_cast<const UnitEffect *>(v.get<utility::Variant::Pointer>()));
            break;
        default:
            EngineObject::ObserverWrapper::update(o, event_type, v);
            break;
    }
}
