#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include <random>

#include "engine_traits.h"

/*!
 * \brief Abstract class used to control units in a battle.
 * \sa BattleEngine, Unit
 */
class UnitController {

public:

    using AngleType = Traits<BattleEngine>::AngleType;

    /*!
     * \brief This class is used as a interface for receiving inputs from the user.
     */
    class UserInterface;

    /*!
     * \brief Construct an UnitController
     * \param fast indicate if the controller computes fast, if so it will be able to perform optimizations, true by default
     * \param show_buttons if true the buttons showing the skills options will be displayed in the turn of an unit <!--
     * --> controlled by this object, by default false
     * \param show_arrow if true, when the chosen skill need an angle, an arrow will be displayed, by default false
     */
    UnitController(bool fast = true, bool show_buttons = false, bool show_arrow = false) :
        _show_buttons(show_buttons), _show_arrow(show_arrow), _fast(fast) {}

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *) = 0;
    virtual AngleType chooseAngle(const Unit *, const Map *, UserInterface *) = 0;

    virtual UnitController *clone() const = 0;

    bool showButtons() const { return _show_buttons; }
    bool showArrow() const { return _show_arrow; }
    bool isFast() const { return _fast; }

protected:

    static std::mt19937 generator;

private:

    bool _show_buttons;
    bool _show_arrow;
    bool _fast;
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
