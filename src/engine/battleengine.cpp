
#include <thread>

#include "battleengine.h"
#include "battlewidget.h"
#include "unitcontroller.h"

BattleEngine::BattleEngine(BattleWidget *interface) : _map(Traits<Map>::width, Traits<Map>::height),
    _interface(interface), _cur_obj(0), _max_speed(1), _t(nullptr), _game_status(status::WORKING) {

}

BattleEngine::~BattleEngine() {

    _delete_thread();

    for(auto& v : _objects) delete v.object;
}

Unit *BattleEngine::addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team) {

    Unit *u = new Unit(unit_info, controller, &_map, team, _interface);
    _map.resolvePendings();

    _objects.push_back(ContainerContent{ u, 0 });

    u->attachObserver(this);
    unit_info->init(u);

    if(u->baseSpeed() > _max_speed) _max_speed = u->baseSpeed();

    return u;
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

    _map.removeObject(u);

    if(_map.gameEndVerify()) _game_status = status::FINISHING;

    if(u->baseSpeed() == _max_speed) {

        _max_speed = 1;
        for(UIntegerType i = 0; i < _map.unitsNumber(); i++) {

            Unit::SpeedType speed = _map.unitAccess(i)->unitInfo()->speed();
            if(speed > _max_speed) _max_speed = speed;
        }
    }
}

bool BattleEngine::_step_loop(){

    if(_cur_obj >= _objects.size()) _cur_obj = 0;

    for(; _cur_obj < _objects.size(); _cur_obj++) {

        auto &object = _objects[_cur_obj].object;
        auto &to_perform = _objects[_cur_obj].to_perform;

        to_perform += (RealType(object->effectiveSpeed())/_max_speed);
        while(to_perform >= 1){

            to_perform -= 1;

            if(object->needThreadToAct()) {

                _t = new std::thread(_perform_internal, object, this);
                return false;
            }
            else object->act();
        }
    }

    return true;
}

void BattleEngine::_delete_thread() {

    if(_t != nullptr) {

        if(_t->joinable()) _t->detach();
        delete _t;

        _t = nullptr;
    }
}

void BattleEngine::_perform_internal(EngineObject *o, BattleEngine *e) {

    o->act();

    e->_step_mut.unlock();
}
