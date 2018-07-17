
#ifndef CONTROLLERS_AI_SLIME_H
#define CONTROLLERS_AI_SLIME_H

#include "unitcontroller.h"

namespace controller {

namespace AI {

class Slime : public UnitController {

protected:

    Slime() {}

public:

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    static Slime *getController() { if(!_controller) _controller = new Slime; return _controller; }

private:

    static Slime *_controller;
};

} /* namespace AI */

} /* namespace controller */

#endif // CONTROLLERS_AI_SLIME_H
