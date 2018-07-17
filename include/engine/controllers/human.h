
#ifndef CONTROLLERS_HUMAN
#define CONTROLLERS_HUMAN

#include "unitcontroller.h"

namespace controller {

class Human : public UnitController {

protected:

    Human() : UnitController(false) {}

public:

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    static Human *getController() { if(!_controller) _controller = new Human; return _controller; }

private:

    static Human *_controller;
};

} /* namespace Controllers */

#endif // CONTROLLERS_HUMAN
