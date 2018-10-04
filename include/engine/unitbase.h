
#ifndef UNITBASE_H
#define UNITBASE_H

#include "unitinfo.h"
#include "engineobject.h"

/*!
 * \brief Class for the basic info that an unit engine have
 * \sa UnitInfo, Unit
 */
class UnitBase : public EngineObject {

public:

    using HealthType = Traits<Unit>::HealthType;
    using EnergyType = Traits<Unit>::EnergyType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;

    /*!
     * \brief Construct an UnitBase passing UnitInfo, UnitInfo must be valid
     * \param info UnitInfo with the basic information of the type of this unit
     * \param m Map where the unit is
     */
    UnitBase(const UnitInfo *info, EngineMap *m);

    virtual ~UnitBase() {}

    /*!
     * \brief Return the UnitInfo associated with this object
     * \return The UnitInfo of this unit type
     */
    const UnitInfo *unitInfo() const { return _info; }

    /*!
     * \brief Set a value to the health of the unit
     * \param health The health the unit will have
     * \sa health()
     */
    void setHealth(HealthType health);

    /*!
     * \brief Return the amount of health the unit have
     * \return The value of health of the unit
     */
    HealthType health() const { return _health; }

    /*!
     * \brief Return the max amount of healht the unit can have
     * \return The max value for health this unit can have
     */
    HealthType maxHealth() const { return _info->health(); }

    void setEnergy(EnergyType energy) { _energy = energy; }

    EnergyType energy() const { return _energy; }

    EnergyType maxEnergy() const { return _info->energy(); }

private:

    const UnitInfo *_info;

    HealthType _health;
    EnergyType _energy;
};

#endif // UNITBASE_H
