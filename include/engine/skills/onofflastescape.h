
#ifndef ONOFFLASTESCAPE_H
#define ONOFFLASTESCAPE_H

#include "unitskill.h"

namespace skill {

/*!
 * \brief UnitSkill to add or remove(on/off), LastEscape effect
 */
class OnOffLastEscape : public UnitSkill {

protected:

    OnOffLastEscape() : UnitSkill(false) {}

public:

    /*!
     * \brief Add LastEscape effect if it's off and remove it if it's on
     */
    virtual UIntegerType action(Unit *, Map *, const Info&) override;

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static OnOffLastEscape *getSkill() {

        if(!_skill) _skill =  new OnOffLastEscape;

        return _skill;
    }

private:

    static OnOffLastEscape *_skill;
};

} /* namespace skill */


#endif // ONOFFLASTESCAPE_H
