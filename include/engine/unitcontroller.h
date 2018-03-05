#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "engine_traits.h"

class UnitController {

public:

    using AngleType = Traits<BattleEngine>::AngleType;

    class UserInterface;

    UnitController(bool show_buttons = false, bool show_arrow = false) : _show_buttons(show_buttons), _show_arrow(show_arrow) {}

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *) = 0;
    virtual AngleType chooseAngle(const Unit *, const Map *, UserInterface *) = 0;

    virtual UnitController *clone() const = 0;

    bool showButtons() const { return _show_buttons; }
    bool showArrow() const { return _show_arrow; }

private:

    bool _show_buttons;
    bool _show_arrow;
};

class UnitController::UserInterface {

public:

    UIntegerType askSkill() { return this->controllerUserInterfaceAskSkillInput(); }
    UnitController::AngleType askAngle() { return this->controllerUserInterfaceAskAngleInput(); }

protected:

    virtual UIntegerType controllerUserInterfaceAskSkillInput() { return 0; }
    virtual UnitController::AngleType controllerUserInterfaceAskAngleInput() { return 0; }
};

#endif // UNITCONTROLLER_H
