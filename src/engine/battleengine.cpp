
#include "traits.h"
#include "battleengine.h"
#include "battlewidget.h"
#include "unit.h"

BattleEngine::~BattleEngine() {

    _delete_thread();

    for(Unit *unit : _units) delete unit;
}

Unit *BattleEngine::addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team) {

    _units.push_back(new Unit(unit_info, controller, &_map, team, _interface));
    _map.addUnit(_units.back());

    _units.back()->attachObserver(this);
    unit_info->init(_units.back());

    return _units.back();
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

            if(_units[i]->isDead()) continue;
        }
    }
}

void BattleEngine::unitDeathEvent(Unit *u) {

    _map.removeUnit(u);

    if(_map.gameEndVerify()) _game_status = status::FINISHING;
}

bool BattleEngine::_step_loop(){

    if(_cur_unit >= _units.size()) _cur_unit = 0;

    for(; _cur_unit < _units.size(); _cur_unit++) {

        auto &unit = _units[_cur_unit];
        auto controller = unit->controller();

        if(unit->isDead()) continue;

        if(unit->isPerformingSkill()) unit->perform();
        else {

            _ask_controller(unit, controller);

            return false;
        }
    }

    return true;
}

void BattleEngine::_ask_controller(Unit * const & unit, const Controller * controller){

    _delete_thread();

    if(controller->isFast()) _ask_controller_internal(unit, this);
    else _t = new std::thread(_ask_controller_internal, unit, this);
}

void BattleEngine::_delete_thread() {

    if(_t != nullptr) {

        if(_t->joinable()) _t->detach();
        delete _t;

        _t = nullptr;
    }
}

void BattleEngine::_ask_controller_internal(Unit *u, BattleEngine *e) {

    u->select();
    u->choose();
    u->unselect();

    e->_cur_unit++;

    e->_step_mut.unlock();
}
