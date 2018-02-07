
#ifndef CONTROLLERS_HUMAN
#define CONTROLLERS_HUMAN

#include "unitcontroller.h"

namespace controller {

class Human : public UnitController {

public:

    Human() : UnitController(true) {}

    virtual UIntegerType choose(Unit *, Map *, BattleEngine *);

    virtual UnitController *clone() const { return new Human(); }
};

} /* namespace Controllers */



#endif // CONTROLLERS_HUMAN
