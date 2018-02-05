
#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include <thread>
#include <mutex>

#include "traits.h"
#include "map.h"
#include "unit.h"

class BattleEngine {

    using Controller = UnitController;

public:

    BattleEngine(BattleWidget *interface) : _map(800, 400), _interface(interface), _cur_unit(0),
        _waiting_arrow_input(false), _t(nullptr) {}
    ~BattleEngine();

    void addUnit(const UnitInfo *unit_info, Controller *, UIntegerType team);

    void step();

    void setScene(QGraphicsScene *scene) { _map.setScene(scene); }
    QGraphicsScene *scene() const { return _map.scene(); }

    void placeUnits() { _map.placeUnits(); }

    bool skillButtonsVisible() const;

    UIntegerType askSkill();

private:

    struct UnitEngineInfo {

        template<typename... Args>
        UnitEngineInfo(Controller *c, Args... args);

        bool performingSkill() { return skill < unit->unitInfo()->skills(); }
        void finishSkill() { skill = unit->unitInfo()->skills(); }

        Unit * const unit;
        Controller * const controller;
        UIntegerType step;
        RealType angle;
        UIntegerType nextCall;
        UIntegerType skill;
    };

    bool _step_loop();
    void _skill_step(Unit * const &, UnitEngineInfo&);
    void _ask_controller(Unit * const &, Controller * const &, UnitEngineInfo&);
    static void _get_direction_step(Unit * const &, Controller * const &, BattleEngine *, UnitEngineInfo *);

    static void _step_internal(Unit *, Controller *, BattleEngine *, UIntegerType *);

    void _delete_thread();

    Map _map;
    BattleWidget *_interface;

    UIntegerType _cur_unit;
    std::vector<UnitEngineInfo> _units;

    bool _waiting_arrow_input;

    std::mutex _step_mut;
    std::thread *_t;
};

#endif // BATTLEENGINE_H
