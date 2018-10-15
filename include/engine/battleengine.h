
#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include <mutex>

#include "enginemap.h"
#include "unit.h"
#include "projectile.h"

namespace std {
class thread;
} /* namespace std */

/*!
 * \brief This class manage controller and skills calls and animation step.
 * \brief Each time 'step' is called, the battle and animation progress a quantum.
 * \sa EngineMap, BattleWidget, BattleEngine::step()
 */
class BattleEngine : Unit::Observer {

    using Controller = UnitController;

public:

    /*!
     * \brief Construct an BattleEngine object using a BattleWidget object.
     * \param interface interface used to get user's input.
     */
    explicit BattleEngine(BattleWidget *interface);

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

    Projectile *addProjectile(ProjectileFactory *factory, const Unit *creator,
                              Projectile::AngleType dir, Projectile::PointType pos, Projectile::AngleType angle);

    /*!
     * \brief Progress the battle by a quantum, it will do nothing if the game's waiting input.
     */
    void step();

    /*!
     * \brief Choose an initial position for every unit in the battle.
     */
    void placeUnits() { _map.resolvePendings(); _map.placeUnits(); }

    /*!
     * \brief Return if the game has finished
     * \return true if the game has finished, false otherwise
     */
    bool finished() const { return _game_status == status::FINISHED; }

    /*!
     * \brief Return the team that won the battle, if the game hasn't finished the return will be one of the teams
     * \return The number of the team that has won
     */
    UIntegerType winningTeam() const { return _map.unitAccess(0)->team(); }

private:

    void unitDeathEvent(Unit *u);

    bool _step_loop();

    void _object_act(EngineObject *obj) { if(!obj->act()) _map.removeObject(obj); }

    static void _perform_internal(EngineObject *, BattleEngine *);

    void _delete_thread();

    EngineMap _map;
    BattleWidget *_interface;

    UIntegerType _cur_obj;

    struct ContainerContent { EngineObject *object; RealType to_perform; };
    std::vector<ContainerContent> _objects;
    std::vector<ContainerContent> _destroyed_objects;

    Unit::SpeedType _max_speed;

    std::mutex _step_mut;
    std::thread *_t;

    enum class status : UIntegerType { WORKING, FINISHING, FINISHED };
    status _game_status;
};

#endif // BATTLEENGINE_H
