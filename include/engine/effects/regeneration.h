
#ifndef EFFECTS_REGENERATION_H
#define EFFECTS_REGENERATION_H

#include <memory/onecopymemorymanager.h>

#include "uniteffect.h"

namespace effect {

class Regeneration : public UnitEffect {

    Regeneration(HealthType amount, UIntegerType period) : _amount(amount), _period(period) {}

public:

    virtual void doTurnEffect(Unit *u, UIntegerType duration_left) const override;

    template <typename... Args>
    static const UnitEffect *getEffect(Args... args) { return _effects.get(Regeneration(args...)); }

private:

    static Regeneration *_clone(const Regeneration& other) { return new Regeneration(other); }

    HealthType _amount;
    UIntegerType _period;

    struct RegCompare {

        bool operator() (const Regeneration& r1, const Regeneration& r2) const {

            if(r1._amount != r2._amount) return r1._amount < r2._amount;
            return r1._period < r2._period;
        }
    };

    static OneCopyMemoryManager<Regeneration, RegCompare> _effects;
};

} /* namespace effect */

#endif // EFFECTS_REGENERATION_H
