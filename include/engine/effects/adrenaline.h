
#ifndef EFFECTS_ADRENALINE_H
#define EFFECTS_ADRENALINE_H

#include "uniteffect.h"

namespace effect {

class Adrenaline : public UnitEffect {

    Adrenaline() {}

public:

    virtual SpeedType doSpeedEffect(const Unit *, SpeedType s) const override { return 1.3*s; }

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static Adrenaline *getEffect() { if(!_copy) _copy = new Adrenaline; return _copy; }

private:

    static Adrenaline *_copy;
};

} /* namespace effect */

#endif // EFFECTS_ADRENALINE_H
