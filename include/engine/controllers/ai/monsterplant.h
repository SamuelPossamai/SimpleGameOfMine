
#ifndef CONTROLLERS_MONSTERPLANT_H
#define CONTROLLERS_MONSTERPLANT_H

#include "unitcontroller.h"

namespace controller {

namespace AI {

class MonsterPlant : public UnitController {

    MonsterPlant() {}

public:

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    static MonsterPlant *getController() { if(!_controller) _controller = new MonsterPlant; return _controller; }

private:

    static MonsterPlant *_controller;
};

} /* namespace controller */

} /* namespace AI */

#endif // CONTROLLERS_MONSTERPLANT_H
