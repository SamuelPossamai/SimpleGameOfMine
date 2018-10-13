
#ifndef SKILLS_TELEPORT_H
#define SKILLS_TELEPORT_H

#include <engine/unitskill.h>

namespace skill {

/*!
 * \brief UnitSkill that teleport an unit to a random place
 */
class Teleport : public UnitSkill {

protected:

    Teleport() : UnitSkill(false) {}

public:

    /*!
     * \brief Call teleportUnit one time, and wait ten turns between the calls
     */
    virtual UIntegerType action(Unit *, EngineMap *, ProjectileCreationInterface&, const Info&) override;

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static Teleport *getSkill() {

        if(!_skill) _skill =  new Teleport;

        return _skill;
    }

    /*!
     * \brief Teleport unit to a random place, it may not work if there is obstacles in the map, try some more times if failed
     * \brief The angle of the unit will also be changed
     * \param u Unit that will be teleported
     * \return true if it works succesfully, false otherwise
     */
    static bool teleportUnit(Unit *u);

private:

    static Teleport *_skill;

};

} /* namespace skill */

#endif // SKILLS_TELEPORT_H
