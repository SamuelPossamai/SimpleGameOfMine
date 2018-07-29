
#ifndef EFFECTS_LASTESCAPE_H
#define EFFECTS_LASTESCAPE_H

#include <memory/onecopymemorymanager.h>

#include "uniteffect.h"

namespace effect {

/*!
 * \brief UnitEffect LastEscape is an effect that consume energy when attacked to escape the attack and teleport to somewhere else
 */
class LastEscape : public UnitEffect {

    LastEscape() {}

public:

    virtual AttackType doDefenseEffect(Unit *def, Unit *att, AttackType a) const override;

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static LastEscape *getEffect() { if(!_copy) _copy = new LastEscape; return _copy; }

private:

    static LastEscape *_copy;
};

} /* namespace effect */

#endif // EFFECTS_LASTESCAPE_H
