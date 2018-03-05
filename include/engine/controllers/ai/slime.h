
#ifndef SLIME_AI_H
#define SLIME_AI_H

#include "unitcontroller.h"

namespace controller {

namespace AI {

class Slime : public UnitController {

public:

    Slime() {}

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual AngleType chooseAngle(const Unit *, const Map *, UserInterface *);

    virtual UnitController *clone() const { return new Slime(); }

};

} /* namespace AI */

} /* namespace controller */

#endif // SLIME_AI_H
