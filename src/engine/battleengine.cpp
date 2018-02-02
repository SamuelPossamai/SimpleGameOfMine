
#include "battleengine.h"
#include "battlewidget.h"
#include "unit.h"
#include "unitcontroller.h"

BattleEngine::~BattleEngine() {

    for(UIntegerType i = 0; i < _map.units(); i++) delete _map.unitAccess(i);
}

void BattleEngine::addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team) {

    _units.emplace_back(controller, unit_info, team);
    _map.addUnit(_units.back().unit);
}

bool BattleEngine::skillButtonsVisible() const {

    return _interface->skillButtonsVisible();
}

UIntegerType BattleEngine::askSkill() {

    return _interface->askSkill();
}

void BattleEngine::step(){

    if(_step_mut.try_lock()) {

        if(_step_loop()) _step_mut.unlock();
    }

    for(UIntegerType i = 0; i < _units.size(); i++) _units[i].unit->animationStep();
}

bool BattleEngine::_step_loop(){

    if(_cur_unit >= _units.size()) _cur_unit = 0;

    for(; _cur_unit < _units.size(); _cur_unit++) {

        auto &unitEInfo = _units[_cur_unit];
        auto &unit = unitEInfo.unit;
        auto &controller = unitEInfo.controller;

        if(unitEInfo.performingSkill()) _skill_step(unit, unitEInfo);
        else {

            _ask_controller(unit, controller, unitEInfo);

            return false;
        }
    }

    return true;
}

void BattleEngine::_skill_step(Unit * const & unit, UnitEngineInfo& unitEInfo) {

    if(unitEInfo.nextCall == unitEInfo.step){

        unitEInfo.nextCall = unit->unitInfo()->callSkill(unitEInfo.skill, unit, &_map, unitEInfo.step);

        if(unitEInfo.nextCall <= unitEInfo.step) unitEInfo.finishSkill();
    }

    unitEInfo.step++;
}

void BattleEngine::_ask_controller(Unit * const & unit, Controller * const & controller, UnitEngineInfo& unitEInfo){

    if(controller->showButtons()) _interface->showSkillButtons(const_cast<UnitInfo *>(unit->unitInfo()));

    if(_t != nullptr) {

        if(_t->joinable()) _t->detach();
        delete _t;
    }

    unitEInfo.step = unitEInfo.nextCall = 0;

    _t = new std::thread(_step_internal, unit, controller, this, &unitEInfo.skill);

    _cur_unit++;
}

void BattleEngine::_step_internal(Unit *unit, Controller *controller, BattleEngine *e, UIntegerType *result) {

    *result = controller->choose(unit, &e->_map, e);

    e->_step_mut.unlock();
}

// it's a private nested class, so it will not be used outside this file, so this method can be declared here
template<typename... Args>
BattleEngine::UnitEngineInfo::UnitEngineInfo(Controller *c, Args... args) : unit(new Unit(args...)), controller(c), step(0) {

    skill = unit->unitInfo()->skills();
}
