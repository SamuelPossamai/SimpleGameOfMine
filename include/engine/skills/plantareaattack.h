
#ifndef SKILLS_PLANTAREAATTACK_H
#define SKILLS_PLANTAREAATTACK_H

#include "unitskill.h"

namespace skill {

/*!
 * \brief UnitSkill to add or remove(on/off), LastEscape effect
 */
class PlantAreaAttack : public UnitSkill {

protected:

    PlantAreaAttack() : UnitSkill(false) {}

public:

    virtual UIntegerType action(Unit *, Map *, const Info&) override;

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static PlantAreaAttack *getSkill() {

        if(!_skill) _skill =  new PlantAreaAttack;

        return _skill;
    }

private:

    static PlantAreaAttack *_skill;
};

} /* namespace skill */

#endif // SKILLS_PLANTAREAATTACK_H
