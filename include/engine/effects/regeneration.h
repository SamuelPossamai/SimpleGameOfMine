
#ifndef EFFECTS_REGENERATION_H
#define EFFECTS_REGENERATION_H

#include <set>

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

        Regeneration r(args...);

        auto it = _effects.find(&r);

        if(it != _effects.end()) return *it;

        Regeneration *new_r = new Regeneration(args...);

        _effects.insert(new_r);

        return new_r;
    }

private:

    HealthType _amount;
    UIntegerType _period;

    struct RegCompare {

        bool operator() (Regeneration * const & r1, Regeneration * const & r2) {

            if(r1->_amount < r2->_amount) return true;
            if(r1->_period < r2->_amount) return true;

            return false;
        }
    };

    static std::set<Regeneration *, RegCompare> _effects;
};

} /* namespace effect */

#endif // EFFECTS_REGENERATION_H
