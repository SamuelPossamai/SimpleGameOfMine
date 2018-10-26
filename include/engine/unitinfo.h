
#ifndef UNITINFO_H
#define UNITINFO_H

#include <vector>

#include <QPixmap>

#include "engine_traits.h"
#include "unitskill.h"

/*!
 * \brief Class with basic information about an unit
 */
class UnitInfo {

public:

    using HealthType = Traits<Unit>::HealthType;
    using EnergyType = Traits<Unit>::EnergyType;
    using AttackType = Traits<Unit>::AttackType;
    using DefenseType = Traits<Unit>::DefenseType;
    using SizeType = Traits<Unit>::SizeType;
    using SpeedType = Traits<Unit>::SpeedType;
    using Attributes = UnitAttributes;

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

    /*!
     * \brief Return the base attack of the unit, it's used to calculate the damage dealt by skills
     * \return The unit's base attack
     */
    AttackType baseAttack(const Attributes& attr, UIntegerType level) const { return attackCalculate(attr, level); }

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

    /*!
     * \brief Return the icon of a skill
     * \param n The id of the skill, a call to this method with an invalid id have undefined behavior
     * \return The icon of a skill
     */
    const QPixmap& skillIcon(UIntegerType n) const { return _skills[n].second; }

    /*!
     * \brief Perform a call to a skill
     * \param n The skill's id, if it's invalid it will have undefined behavior
     * \param u The unit that is performing the skill
     * \param m Map containing the units in the battle
     * \param pci Interface to create projectiles.
     * \param info Basic information about the call
     * \sa UnitSkill
     * \return After how many steps the skill should be performed again
     */
    UIntegerType callSkill(UIntegerType n, Unit *u, Map *m,
                           UnitSkill::ProjectileCreationInterface& pci, const UnitSkill::Info& info) const;

    /*!
     * \brief Verify if a skill needs angle
     * \param n The skill's id, if it's invalid the behavior will be undefined
     * \return true if it needs an angle, false otherwise
     */
    bool skillNeedAngle(UIntegerType n) const { return _skills[n].first->needAngle(); }

    /*!
     * \brief Return the number of skills
     * \return The numbers of skills
     */
    UIntegerType skills() const { return _skills.size(); }

    /*!
     * \brief Virtual method called when an unit is created
     * \param u Unit just created
     */
    virtual void init(Unit *u) const { Q_UNUSED(u); }

protected:

    /*!
     * \brief Add a skill to the unit information
     * \param skill Skill that will be added
     * \param icon Icon of the skill that will be added, by default blank
     */
    void addSkill(UnitSkill *skill, const QPixmap& icon = QPixmap()) { _skills.emplace_back(skill, icon); }

    virtual HealthType healthCalculate(const Attributes&, UIntegerType) const = 0;
    virtual EnergyType energyCalculate(const Attributes&, UIntegerType) const = 0;
    virtual AttackType attackCalculate(const Attributes&, UIntegerType) const = 0;
    virtual SpeedType speedCalculate(const Attributes&, UIntegerType) const = 0;
    virtual SizeType sizeCalculate(const Attributes&, UIntegerType) const = 0;

private:

    using SkillVector = std::vector<std::pair<UnitSkill *, QPixmap> >;

    SkillVector _skills;
};

#endif // UNITINFO_H
