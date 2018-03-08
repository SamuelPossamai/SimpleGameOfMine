
#include <iostream>

#include "traits.h"
#include "battleengine.h"
#include "battlewidget.h"
#include "unit.h"

BattleEngine::~BattleEngine() {

    _delete_thread();

    for(UIntegerType i = 0; i < _map.units(); i++) delete _map.unitAccess(i);
}

void BattleEngine::addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team) {

    _units.emplace_back(controller, unit_info, team, _interface);
    _map.addUnit(_units.back().unit);

    _units.back().unit->setHandler(this);
}

void BattleEngine::step(){

    if(_step_mut.try_lock()) {

        _interface->hideSkillButtons();
        _interface->hideArrow();

        if(_step_loop()) _step_mut.unlock();

    }else {

        for(UIntegerType i = 0; i < _units.size(); i++) {

            if(!_units[i].unit->isDead()) continue;

            if(!_units[i].performingSkill() || _units[i].step == 0) _units[i].unit->animationStep();
        }
    }
}

bool BattleEngine::_step_loop(){

    if(_cur_unit >= _units.size()) _cur_unit = 0;

    for(; _cur_unit < _units.size(); _cur_unit++) {

        auto &unitEInfo = _units[_cur_unit];
        auto &unit = unitEInfo.unit;
        auto &controller = unitEInfo.controller;

        if(unit->isDead()) continue;

        if(unitEInfo.performingSkill()) {

            if(_waiting_arrow_input) {

                if(controller->showArrow()) _interface->showArrow(unit->x(), unit->y());

                _delete_thread();

                if(controller->isFast()) _get_direction_step(unit, controller, this, &unitEInfo);
                else _t = new std::thread(_get_direction_step, unit, controller, this, &unitEInfo);

                _waiting_arrow_input = false;

                return false;
            }
            else _skill_step(unit, unitEInfo);
        }
        else {

            _ask_controller(unit, controller, unitEInfo);

            return false;
        }

        unit->animationStep();
    }

    return true;
}

void BattleEngine::_get_direction_step(Unit * const & u, Controller * const & c, BattleEngine *e, UnitEngineInfo *unitEInfo) {

    unitEInfo->angle = c->chooseAngle(u, &e->_map, e->_interface);

    e->_cur_unit++;

    e->_step_mut.unlock();
}

void BattleEngine::_skill_step(Unit * const & unit, UnitEngineInfo& unitEInfo) {

    if(unitEInfo.step == 0) {

        unit->startSkillAnimation(unitEInfo.skill);

        unit->removeSelectEffect();
    }

    if(unitEInfo.nextCall == unitEInfo.step){

        unitEInfo.nextCall = unitEInfo.step + \
                unit->unitInfo()->callSkill(unitEInfo.skill, unit, &_map, { unitEInfo.step, unitEInfo.angle });

        if(unitEInfo.nextCall <= unitEInfo.step) {

            unit->endSkillAnimation();
            unitEInfo.finishSkill();
        }
    }

    unitEInfo.step++;
}

void BattleEngine::_ask_controller(Unit * const & unit, Controller * const & controller, UnitEngineInfo& unitEInfo){

    if(controller->showButtons()) _interface->showSkillButtons(unit->unitInfo());

    _delete_thread();

    if(!controller->isFast()) unit->selectEffect();

    _units[(_cur_unit != 0) ? _cur_unit - 1 : _units.size() - 1].unit->removeSelectEffect();

    unitEInfo.step = unitEInfo.nextCall = 0;

    if(controller->isFast()) _step_internal(unit, controller, this, &unitEInfo.skill);
    else _t = new std::thread(_step_internal, unit, controller, this, &unitEInfo.skill);
}

void BattleEngine::_delete_thread() {

    if(_t != nullptr) {

        if(_t->joinable()) _t->detach();
        delete _t;

        _t = nullptr;
    }
}

void BattleEngine::_step_internal(Unit *unit, Controller *controller, BattleEngine *e, UIntegerType *result) {

    *result = controller->chooseSkill(unit, &e->_map, e->_interface);

    if(unit->unitInfo()->skillNeedAngle(*result)) e->_waiting_arrow_input = true;
    else e->_cur_unit++;

    e->_step_mut.unlock();
}

// it's a private nested class, so it will not be used outside this file and this method can be declared here
template<typename... Args>
BattleEngine::UnitEngineInfo::UnitEngineInfo(Controller *c, Args... args) : unit(new Unit(args...)), controller(c), step(0) {

    skill = unit->unitInfo()->skills();
}
