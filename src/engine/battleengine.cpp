
#include "traits.h"
#include "battleengine.h"
#include "battlewidget.h"
#include "unit.h"

BattleEngine::~BattleEngine() {

    _delete_thread();

    for(UnitEngineInfo& ueinfo : _units) delete ueinfo.unit;
}

void BattleEngine::addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team) {

    _units.emplace_back(unit_info, controller, &_map, team, _interface);
    _map.addUnit(_units.back().unit);

    _units.back().unit->attachHandler(this);
}

void BattleEngine::step(){

    if(_game_status == status::FINISHED) return;
    if(_game_status == status::FINISHING) {

        _interface->displayMessage("Team " + std::to_string(_map.unitAccess(0)->team()) + " Won");

        _game_status = status::FINISHED;

        return;
    }

    if(_step_mut.try_lock()) {

        if(_step_loop()) _step_mut.unlock();

    }else {

        for(UIntegerType i = 0; i < _units.size(); i++) {

            if(_units[i].unit->isDead()) continue;

            if(!_units[i].performingSkill() || _units[i].step == 0) _units[i].unit->animationStep();
        }
    }
}

void BattleEngine::unitHandlerDeathEvent(Unit *u) {

    u->hideAnimation();
    _map.removeUnit(u);

    if(_map.gameEndVerify()) _game_status = status::FINISHING;
}

bool BattleEngine::_step_loop(){

    if(_cur_unit >= _units.size()) _cur_unit = 0;

    for(; _cur_unit < _units.size(); _cur_unit++) {

        auto &unitEInfo = _units[_cur_unit];
        auto &unit = unitEInfo.unit;
        auto controller = unit->controller();

        if(unit->isDead()) continue;

        if(unitEInfo.performingSkill()) _skill_step(unit, unitEInfo);
        else {

            _ask_controller(unit, controller, unitEInfo);

            return false;
        }

        unit->animationStep();
    }

    return true;
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

void BattleEngine::_ask_controller(Unit * const & unit, const Controller * controller, UnitEngineInfo& unitEInfo){

    _delete_thread();

    if(!controller->isFast()) unit->selectEffect();

    _units[(_cur_unit != 0) ? _cur_unit - 1 : _units.size() - 1].unit->removeSelectEffect();

    unitEInfo.step = unitEInfo.nextCall = 0;

    if(controller->isFast()) _step_internal(unit, this, &unitEInfo);
    else _t = new std::thread(_step_internal, unit, this, &unitEInfo);
}

void BattleEngine::_delete_thread() {

    if(_t != nullptr) {

        if(_t->joinable()) _t->detach();
        delete _t;

        _t = nullptr;
    }
}

void BattleEngine::_step_internal(Unit *u, BattleEngine *e, UnitEngineInfo *unitEInfo) {

    auto p = u->choose();

    unitEInfo->skill = p.first;
    unitEInfo->angle = p.second;

    e->_cur_unit++;

    e->_step_mut.unlock();
}

// it's a private nested class, so it will not be used outside this file and this method can be declared here
template<typename... Args>
BattleEngine::UnitEngineInfo::UnitEngineInfo(Args... args) : unit(new Unit(args...)), step(0) {

    skill = unit->unitInfo()->skills();
}
