
#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include <thread>
#include <mutex>

#include "map.h"
#include "unit.h"
#include "unitcontroller.h"

/*!
 * \brief This class manage controller and skills calls and animation step.
 * \brief Each time 'step' is called, the battle and animation progress a quantum.
 * \sa Map, BattleWidget, BattleEngine::step()
 */
class BattleEngine : Unit::Handler {

    using Controller = UnitController;

public:

    /*!
     * \brief Construct an BattleEngine object using a BattleWidget object.
     * \param interface interface used to get user's input.
     */
    BattleEngine(BattleWidget *interface) : _map(800, 400), _interface(interface), _cur_unit(0),
        _waiting_arrow_input(false), _t(nullptr) {}

    ~BattleEngine();

    /*!
     * \brief add an unit to the BattleEngine
     * \sa placeUnits()
     * \param unit_info information about the unit that will be added, including animation
     * \param controller the unit controller, it controls the decisions for the unit
     * \param team unit team, it determines if other units are allies or enemies
     */
    void addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team);

    /*!
     * \brief Progress the battle by a quantum, it will do nothing if the game's waiting input.
     */
    void step();

    /*!
     * \brief Set a scene for the unit's animation.
     * \param scene scene that will be set.
     */
    void setScene(QGraphicsScene *scene) { _map.setScene(scene); }

    /*!
     * \brief Return the scene used to display the units.
     * \return Scene that used by the animations.
     */
    QGraphicsScene *scene() const { return _map.scene(); }

    /*!
     * \brief Choose an initial position for every unit in the battle.
     */
    void placeUnits() { _map.placeUnits(); }

private:

    void unitHandlerDeathEvent(Unit *u) { u->hideAnimation(); }

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
