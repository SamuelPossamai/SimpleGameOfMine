
#ifndef UNITINFO_H
#define UNITINFO_H

#include <vector>

#include <QPixmap>

#include <variant.h>

#include "engine_traits.h"
#include "unitskill.h"

/*!
 * \brief Class with basic information about an unit
 */
class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using EnergyType = Traits<Unit>::EnergyType;
    using SpecialType = EnergyType;
    using RageType = EnergyType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;
    using AccuracyType = AttackType;
    using MagicPowerType = AttackType;
    using MagicControlType = MagicPowerType;
    using SizeType = Traits<Unit>::SizeType;
    using SpeedType = Traits<Unit>::SpeedType;
    using Attributes = UnitAttributes;
    using Skills = std::vector<std::pair<std::string, sutils::VariantDataInfo> >;

    /*!
     * \brief Construct an UnitInfo, all the parameters are set to zero
     */
    UnitInfo() = default;

    virtual ~UnitInfo() = default;

    /*!
     * \brief Return the maximum health of the unit
     * \return The maximum health of the unit
     */
    HealthType health(const Attributes& attr, UIntegerType level) const { return healthCalculate(attr, level); }

    /*!
     * \brief Return the maximum energy of the unit
     * \return The maximum energy of the unit
     */
    EnergyType energy(const Attributes& attr, UIntegerType level) const { return energyCalculate(attr, level); }

    SpecialType special(const Attributes& attr, UIntegerType level) const { return specialCalculate(attr, level); }

    RageType rage(const Attributes& attr, UIntegerType level) const { return rageCalculate(attr, level); }

    /*!
     * \brief Return the base attack of the unit, it's used to calculate the damage dealt by skills
     * \return The unit's base attack
     */
    AttackType baseAttack(const Attributes& attr, UIntegerType level) const { return attackCalculate(attr, level); }

    AccuracyType accuracy(const Attributes& attr, UIntegerType level) const { return accuracyCalculate(attr, level); }

    MagicPowerType magicPower(const Attributes& attr, UIntegerType level) const { return magicPowerCalculate(attr, level); }

    MagicControlType magicControl(const Attributes& attr, UIntegerType level) const { return magicControlCalculate(attr, level); }

    /*!
     * \brief Return the size of the unit, the unit is represented by a circle in the engine
     * \return The size of the unit
     */
    SizeType size(const Attributes& attr, UIntegerType level) const { return sizeCalculate(attr, level); }

    /*!
     * \brief The speed of the unit, higher this parameter, more turns the unit will have
     * \return The speed of the unit
     */
    SpeedType speed(const Attributes& attr, UIntegerType level) const { return speedCalculate(attr, level); }

    virtual Skills getSkills(const Unit *) const = 0;

    /*!
     * \brief Virtual method called when an unit is created
     * \param u Unit just created
     */
    virtual void init(Unit *u) const { Q_UNUSED(u) }

protected:

    virtual HealthType healthCalculate(const Attributes&, UIntegerType) const = 0;
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const = 0;
    virtual SpecialType specialCalculate(const Attributes&, UIntegerType) const { return 0; }
    virtual RageType rageCalculate(const Attributes&, UIntegerType) const { return 0; }
    virtual AttackType attackCalculate(const Attributes&, UIntegerType) const = 0;
    virtual AccuracyType accuracyCalculate(const Attributes&, UIntegerType) const = 0;
    virtual MagicPowerType magicPowerCalculate(const Attributes&, UIntegerType) const = 0;
    virtual MagicControlType magicControlCalculate(const Attributes&, UIntegerType) const = 0;
    virtual SpeedType speedCalculate(const Attributes&, UIntegerType) const = 0;
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const = 0;
};

#endif // UNITINFO_H
