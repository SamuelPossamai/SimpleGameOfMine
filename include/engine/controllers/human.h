
#ifndef CONTROLLERS_HUMAN
#define CONTROLLERS_HUMAN

#include "unitcontroller.h"

namespace controller {

class Human : public UnitController {

public:

    Human() : UnitController(true, true) {}

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual AngleType chooseAngle(const Unit *, const Map *, UserInterface *);

    virtual UnitController *clone() const { return new Human(); }
};

} /* namespace Controllers */



#endif // CONTROLLERS_HUMAN
