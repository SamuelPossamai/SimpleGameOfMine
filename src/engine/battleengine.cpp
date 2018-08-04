
#include <thread>

#include "battleengine.h"
#include "battlewidget.h"
#include "unitcontroller.h"

BattleEngine::BattleEngine(BattleWidget *interface) : _map(Traits<Map>::width, Traits<Map>::height),
    _interface(interface), _cur_unit(0), _max_speed(1), _t(nullptr), _game_status(status::WORKING) {

}

BattleEngine::~BattleEngine() {

    _delete_thread();

    for(auto& v : _units) delete v.unit;
}

Unit *BattleEngine::addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team) {

    _units.push_back(ContainerContent{ new Unit(unit_info, controller, &_map, team, _interface), 0 });
    _map.addUnit(_units.back().unit);

    _units.back().unit->attachObserver(this);
    unit_info->init(_units.back().unit);

    if(unit_info->speed() > _max_speed) _max_speed = unit_info->speed();

    return _units.back().unit;
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
    }
}

void BattleEngine::unitDeathEvent(Unit *u) {

    _map.removeUnit(u);

    if(_map.gameEndVerify()) _game_status = status::FINISHING;

    if(u->unitInfo()->speed() == _max_speed) {

        _max_speed = 1;
        for(UIntegerType i = 0; i < _map.units(); i++) {

            Unit::SpeedType speed = _map.unitAccess(i)->unitInfo()->speed();
            if(speed > _max_speed) _max_speed = speed;
        }
    }
}

bool BattleEngine::_step_loop(){

    if(_cur_unit >= _units.size()) _cur_unit = 0;

    for(; _cur_unit < _units.size(); _cur_unit++) {

        auto &unit = _units[_cur_unit].unit;
        auto &to_perform = _units[_cur_unit].to_perform;
        auto controller = unit->controller();

        if(unit->isDead()) continue;

        if(unit->isPerformingSkill()) {

            if((to_perform += (RealType(unit->unitInfo()->speed())/_max_speed)) >= 1){

                to_perform -= 1;
                unit->perform();
            }
        }
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
