#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include <random>
#include <optional>

#include "engine_traits.h"

/*!
 * \brief Abstract class used to control units in a battle.
 * \sa BattleEngine, Unit
 */
class UnitController {

public:

    using AngleType = Traits<BattleEngine>::AngleType;

    class UserInterface;

    /*!
     * \brief Construct an UnitController.
     * \param fast indicate if the controller computes fast, if so it will be able to perform optimizations, true by default.
     */
    explicit UnitController(bool fast = true) : _fast(fast) {}

    virtual ~UnitController() {}

    /*!
     * \brief This method is called when this controller needs to choose an skill in a game's battle.
     * \param u unit that the skill will be chosen for.
     * \param m map containing all units in play.
     * \param i interface for user's input.
     * \return It must return the number of the selected skill
     */
    virtual UIntegerType chooseSkill(const Unit *u, const Map *m, UserInterface *i) = 0;

    /*!
     * \brief This method is called when this controller needs to choose an angle in a game's battle
     * \param u unit that the angle will be chosen for.
     * \param m map containing all units in play.
     * \param i interface for user's input.
     * \return Chosen angle, if it's return does not have a value it means the choice was canceled
     */
    virtual std::optional<AngleType> chooseAngle(const Unit *u, const Map *m, UserInterface *i) = 0;

    bool isFast() const { return _fast; }

private:

    bool _fast;
};

/*!
 * \brief This class is used as a interface for receiving inputs from the user.
 */
class UnitController::UserInterface {

public:

    UIntegerType askSkill(const Unit *u) { return this->controllerUserInterfaceAskSkillInput(u); }
    std::optional<UnitController::AngleType> askAngle(const Unit *u) { return this->controllerUserInterfaceAskAngleInput(u); }

protected:

    virtual UIntegerType controllerUserInterfaceAskSkillInput(const Unit *) = 0;
    virtual std::optional<UnitController::AngleType> controllerUserInterfaceAskAngleInput(const Unit *) = 0;
};

#endif // UNITCONTROLLER_H
