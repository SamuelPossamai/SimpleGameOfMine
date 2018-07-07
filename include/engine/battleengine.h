
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
class BattleEngine : Unit::Observer {

    using Controller = UnitController;

public:

    /*!
     * \brief Construct an BattleEngine object using a BattleWidget object.
     * \param interface interface used to get user's input.
     */
    BattleEngine(BattleWidget *interface) : _map(800, 400), _interface(interface), _cur_unit(0),
        _t(nullptr), _game_status(status::WORKING) {}

    ~BattleEngine();

    /*!
     * \brief Create an unit and add it to the BattleEngine
     * \sa placeUnits()
     * \param unit_info Information about the unit that will be added, including animation
     * \param controller The unit controller, it controls the decisions for the unit
     * \param team Unit team, it determines if other units are allies or enemies
     * \return Return the unit that was just created
     */
    Unit *addUnit(const UnitInfo *unit_info, Controller *controller, UIntegerType team);

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

    void unitDeathEvent(Unit *u);

    bool _step_loop();
    void _ask_controller(Unit * const &, const Controller *);

    static void _ask_controller_internal(Unit *, BattleEngine *);

    void _delete_thread();

    Map _map;
    BattleWidget *_interface;

    UIntegerType _cur_unit;
    std::vector<Unit *> _units;

    std::mutex _step_mut;
    std::thread *_t;

    enum class status : UIntegerType { WORKING, FINISHING, FINISHED };
    status _game_status;
};

#endif // BATTLEENGINE_H
