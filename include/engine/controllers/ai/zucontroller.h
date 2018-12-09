
#ifndef CONTROLLERS_ZUCONTROLLER_H
#define CONTROLLERS_ZUCONTROLLER_H

#include "unitcontroller.h"

namespace controller {

namespace AI {

class ZuController : public UnitController {

    ZuController() {}

public:

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    static ZuController *getController() { if(!_controller) _controller = new ZuController; return _controller; }

private:

    static ZuController *_controller;
};

} /* namespace controller */

} /* namespace AI */

#endif // CONTROLLERS_ZUCONTROLLER_H
