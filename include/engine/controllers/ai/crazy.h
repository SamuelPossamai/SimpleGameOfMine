
#ifndef CONTROLLERS_CRAZY_H
#define CONTROLLERS_CRAZY_H

#include "unitcontroller.h"

namespace controller {

namespace AI {

class Crazy : public UnitController {

    Crazy() {}

public:

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    static Crazy *getController() { if(!_controller) _controller = new Crazy; return _controller; }

private:

    static Crazy *_controller;
};

} /* namespace controller */

} /* namespace AI */

#endif // CONTROLLERS_CRAZY_H
