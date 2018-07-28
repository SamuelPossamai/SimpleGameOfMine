
#ifndef EFFECTS_LASTESCAPE_H
#define EFFECTS_LASTESCAPE_H

#include <memory/onecopymemorymanager.h>

#include "uniteffect.h"

namespace effect {

class LastEscape : public UnitEffect {

    LastEscape() {}

public:

    virtual AttackType doDefenseEffect(Unit *def, Unit *att, AttackType a) const override;

    static LastEscape *getEffect() { if(!_copy) _copy = new LastEscape; return _copy; }

private:

    static LastEscape *_copy;
};

} /* namespace effect */

#endif // EFFECTS_LASTESCAPE_H
