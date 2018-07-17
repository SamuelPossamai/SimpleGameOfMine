
#ifndef EFFECTS_REGENERATION_H
#define EFFECTS_REGENERATION_H

#include <set>

#include <utility/onecopymemorymanager.h>

#include "uniteffect.h"

namespace effect {

class Regeneration : public UnitEffect {

public:

    Regeneration(HealthType amount, UIntegerType period) : _amount(amount), _period(period) {}

    virtual void doTurnEffect(Unit *u, UIntegerType duration_left) const override {

        if(!(duration_left%_period)) u->heal(u, _amount);
    }

    template <typename... Args>
    static const UnitEffect *getEffect(Args... args) {

        return _effects.get(args...);
    }

private:

    HealthType _amount;
    UIntegerType _period;

    struct RegCompare {

        bool operator() (Regeneration& r1, Regeneration& r2) {

            if(r1._amount < r2._amount) return true;
            if(r1._period < r2._amount) return true;

            return false;
        }
    };

    static utility::OneCopyMemoryManager<Regeneration, RegCompare> _effects;
};

} /* namespace effect */

#endif // EFFECTS_REGENERATION_H
