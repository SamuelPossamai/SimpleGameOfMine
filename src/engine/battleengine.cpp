
#include <thread>

#include "projectilefactory.h"
#include "battleengine.h"
#include "battlewidget.h"
#include "unitcontroller.h"

BattleEngine::BattleEngine(BattleWidget *interface) : _map(Traits<EngineMap>::width, Traits<EngineMap>::height),
    _interface(interface), _cur_obj(0), _max_speed(1), _t(nullptr), _game_status(status::WORKING) {

}

BattleEngine::~BattleEngine() {

    _delete_thread();

    for(auto& v : _objects) delete v.object;
}

Unit *BattleEngine::addUnit(const UnitInfo *unit_info, Controller *controller,
                            const UnitAttributes& attr, UIntegerType level, UIntegerType team,
                            const Character *character) {

    Unit *u = new Unit(unit_info, controller, &_map, _interface, attr, level, team, character);
    _map.resolvePendings();

    _objects.push_back(ContainerContent{ u, 0 });

    u->attachObserver(this);
    unit_info->init(u);

    if(u->baseSpeed() > _max_speed) _max_speed = u->baseSpeed();

    return u;
}

Projectile *BattleEngine::addProjectile(ProjectileFactory *factory, const Unit *creator,
                                        Projectile::AngleType dir, Projectile::PointType pos, Projectile::AngleType angle) {

    Projectile *p = factory->create(&_map, creator, dir, pos, angle);
    _map.resolvePendings();

    _objects.push_back(ContainerContent{ p, 0 });

    return p;
}

void BattleEngine::step(){

    if(_game_status == status::FINISHED) return;
    if(_game_status == status::FINISHING) {

        _interface->displayMessage(_map.unitAccess(0)->team() ? "You Lost" : "You Won");

        _game_status = status::FINISHED;

        return;
    }

    if(_step_mut.try_lock()) {

        if(_step_loop()) _step_mut.unlock();
    }
}

void BattleEngine::unitDeathEvent(const Unit *u) {

    if(_map.gameEndVerify()) _game_status = status::FINISHING;

    if(u->baseSpeed() == _max_speed) {

        _max_speed = 1;
        for(UIntegerType i = 0; i < _map.unitsNumber(); i++) {

            Unit::SpeedType speed = _map.unitAccess(i)->baseSpeed();
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
            else _object_act(object);
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

    e->_object_act(o);

    e->_step_mut.unlock();
}
