
#ifndef SKILLS_EVADE_H
#define SKILLS_EVADE_H

#include "unitskill.h"

namespace skill {

/*!
 * \brief This skills walks for a small duration backward
 */
class Evade : public UnitSkill {

protected:

    Evade() : UnitSkill(false) {}

public:

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static Evade *getSkill() {

        if(!_skill) _skill =  new Evade;

        return _skill;
    }

    static UnitSkill *create(const utility::VariantDataInfo&) { return getSkill(); }

    void destroy() override {}

private:

    static Evade *_skill;
};

} /* namespace skill */

#endif // SKILLS_EVADE_H
