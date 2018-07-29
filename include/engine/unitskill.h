
#ifndef UNITSKILL_H
#define UNITSKILL_H

#include <config/types.h>

/*!
 * \brief This is a virtual pure class that represents an unit skill, all skills need to inherit it directly or indirectly.
 * \brief Specific skills are in the skills directory.
 */
class UnitSkill {

public:

    struct Info {

        UIntegerType step;
        RealType angle;
    };

    /*!
     * \brief Used to indicate if tnhis skills need an angle to be performed, the omission in a derived class means it does need.
     * \sa needAngle()
     * \param need_angle If true this skill need to get an angle to be performed, if false it do not have.
     */
    explicit UnitSkill(bool need_angle = true) : _need_angle(need_angle) {}

    virtual ~UnitSkill() {}

    /*!
     * \brief This function is virtual pure and must be implemented in a derived class.
     * \brief This function is called several times, and it determine what the skill does.
     * \param unit The unit that is performing the skill.
     * \param map Object that contains all the units.
     * \param info Information about the skill being performed, including how many steps(timer cycle) has passed.
     * \return Number of steps until the next call to 'action', to stop the skill return 0.
     */
    virtual UIntegerType action(Unit *unit, Map *map, const Info& info) = 0;

    /*!
     * \brief Same as a call to action.
     * \sa action(Unit *, Map *, const Info&)
     * \param unit The unit that is performing thne skill.
     * \param map Object that contains all the units.
     * \param info Information about the skill being performed, including how many steps(timer cycle) has passed.
     * \return Number of steps until the next call to 'action', to stop the skill return 0.
     */
    UIntegerType operator() (Unit *unit, Map *map, const Info& info) { return this->action(unit, map, info); }

    /*!
     * \brief Return true if this skill needs an angle to be performed.
     * \sa UnitSkill(bool)
     * \return true if it needs, false otherwise.
     */
    bool needAngle() const { return _need_angle; }

private:

    const bool _need_angle;
};

#endif // UNITSKILL_H
