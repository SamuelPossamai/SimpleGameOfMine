
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

    /*!
     * \brief Construct an UnitInfo, all the parameters are set to zero
     */
    UnitInfo() : _max_health(0), _max_energy(0), _base_attack(0), _speed(0), _size(0) {}

    virtual ~UnitInfo();

    /*!
     * \brief Return the maximum health of the unit
     * \return The maximum health of the unit
     */
    HealthType health() const { return _max_health; }

    /*!
     * \brief Return the maximum energy of the unit
     * \return The maximum energy of the unit
     */
    EnergyType energy() const { return _max_energy; }

    /*!
     * \brief Return the base attack of the unit, it's used to calculate the damage dealt by skills
     * \return The unit's base attack
     */
    AttackType baseAttack() const { return _base_attack; }

    /*!
     * \brief Return the size of the unit, the unit is represented by a circle in the engine
     * \return The size of the unit
     */
    SizeType size() const { return _size; }

    /*!
     * \brief The speed of the unit, higher this parameter, more turns the unit will have
     * \return The speed of the unit
     */
    SpeedType speed() const { return _speed; }

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
     * \param info Basic information about the call
     * \sa UnitSkill
     * \return After how many steps the skill should be performed again
     */
    UIntegerType callSkill(UIntegerType n, Unit *u, Map *m, const UnitSkill::Info& info) const;

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

    /*!
     * \brief Copy the stats and skills from other UnitInfo
     * \param i UnitInfo that will be copied
     */
    void copy(const UnitInfo *i) { copySkills(i); copyStats(i); }

    /*!
     * \brief Copy the skills from other UnitInfo
     * \param i UnitInfo that will be copied
     */
    void copySkills(const UnitInfo *i) { _skills = i->_skills; }

    /*!
     * \brief Copy the stats from other UnitInfo
     * \param i UnitInfo that will be copied
     */
    void copyStats(const UnitInfo *i);

protected:

    /*!
     * \brief Add a skill to the unit information
     * \param skill Skill that will be added
     * \param icon Icon of the skill that will be added, by default blank
     */
    void addSkill(UnitSkill *skill, const QPixmap& icon = QPixmap()) { _skills.emplace_back(skill, icon); }

    /*!
     * \brief Set the value of the max health for this unit info
     * \param health New value for the max health
     */
    void setHealth(HealthType health) { _max_health = health; }

    /*!
     * \brief Set the value of the max energy for this unit info
     * \param energy New value for the max energy
     */
    void setEnergy(EnergyType energy) { _max_energy = energy; }

    /*!
     * \brief Set the value of the base attack for this unit info
     * \param attack New value for the base attack
     */
    void setBaseAttack(AttackType attack) { _base_attack = attack; }

    /*!
     * \brief Set the value of the speed for this unit info
     * \param speed New value for the speed
     */
    void setSpeed(SpeedType speed) { _speed = speed; }

    /*!
     * \brief Set the value of the size for this unit info
     * \param size New value for the size
     */
    void setSize(SizeType size) { _size = size; }

private:

    using SkillVector = std::vector<std::pair<UnitSkill *, QPixmap> >;

    HealthType _max_health;
    EnergyType _max_energy;
    AttackType _base_attack;
    DefenseType _base_defense;
    SpeedType _speed;

    SizeType _size;

    SkillVector _skills;
};

#endif // UNITINFO_H
