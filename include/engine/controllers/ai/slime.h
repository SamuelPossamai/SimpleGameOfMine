
#ifndef CONTROLLERS_AI_SLIME_H
#define CONTROLLERS_AI_SLIME_H

#include "unitcontroller.h"

namespace controller {

namespace AI {

class Slime : public UnitController {

public:

    Slime() {}

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    virtual UnitController *clone() const { return new Slime(); }

};

} /* namespace AI */

} /* namespace controller */

#endif // CONTROLLERS_AI_SLIME_H
