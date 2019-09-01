
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
    using SpecialType = UnitInfo::SpecialType;
    using RageType = UnitInfo::RageType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;
    using AccuracyType = UnitInfo::AccuracyType;
    using MagicPowerType = UnitInfo::MagicPowerType;
    using MagicControlType = UnitInfo::MagicControlType;
    using Attributes = UnitAttributes;

    /*!
     * \brief Construct an UnitBase passing UnitInfo, UnitInfo must be valid
     * \param info UnitInfo with the basic information of the type of this unit
     * \param m Map where the unit is
     */
    UnitBase(const UnitInfo *info, EngineMap *m, const Attributes& attr, UIntegerType level);

    virtual ~UnitBase();

    /*!
     * \brief Return the UnitInfo associated with this object
     * \return The UnitInfo of this unit type
     */
    const UnitInfo *unitInfo() const { return _info; }

    /*!
     * \brief Return the amount of health the unit has
     * \return The value of health of the unit
     */
    HealthType health() const { return _health; }

    /*!
     * \brief Return the max amount of health the unit can have
     * \return The max value for health this unit can have
     */
    HealthType maxHealth() const { return _info->health(attributes(), level()); }

    /*!
     * \brief Return the amount of energy the unit has
     * \return The value of energy of the unit
     */
    EnergyType energy() const { return _energy; }

    /*!
     * \brief Return the max amount of energy the unit can have
     * \return The max value for energy this unit can have
     */
    EnergyType maxEnergy() const { return _info->energy(attributes(), level()); }

    /*!
     * \brief Return the amount of special the unit has
     * \return The value of special of the unit
     */
    SpecialType special() const { return _special; }

    /*!
     * \brief Return the max amount of special the unit can have
     * \return The max value for special this unit can have
     */
    SpecialType maxSpecial() const { return _info->special(attributes(), level()); }

    /*!
     * \brief Return the amount of rage the unit has
     * \return The value of rage of the unit
     */
    EnergyType rage() const { return _rage; }

    /*!
     * \brief Return the max amount of rage the unit can have
     * \return The max value for rage this unit can have
     */
    EnergyType maxRage() const { return _info->rage(attributes(), level()); }

    AttackType baseDamage() const { return _info->baseAttack(attributes(), level()); }

    AccuracyType accuracy() const { return _info->accuracy(attributes(), level()); }

    MagicPowerType magicPower() const { return _info->magicPower(attributes(), level()); }

    MagicControlType magicControl() const { return _info->magicControl(attributes(), level()); }

    UIntegerType level() const { return _level; }

    const Attributes& attributes() const { return _attr; }

protected:

    /*!
     * \brief Set a value to the health of the unit
     * \param health The health the unit will have
     * \sa health()
     */
    bool setHealth(HealthType health) { return _set_bartype_val(health, maxHealth(), _health); }

    bool setEnergy(EnergyType energy) { return _set_bartype_val(energy, maxEnergy(), _energy); }

    bool setSpecial(SpecialType special) { return _set_bartype_val(special, maxSpecial(), _special); }

    bool setRage(RageType rage) { return _set_bartype_val(rage, maxRage(), _rage); }

private:

    template<typename T>
    bool _set_bartype_val(T new_val, T max, T& val) {

        T prev = val;

        if(new_val > max) val = max;
        else if(new_val <= 0) val = 0;
        else val = new_val;

        return prev != new_val;
    }

    const UnitInfo *_info;

    HealthType _health;
    EnergyType _energy;
    SpecialType _special;
    RageType _rage;
    UIntegerType _level;
    UnitAttributes _attr;
};

#endif // UNITBASE_H
