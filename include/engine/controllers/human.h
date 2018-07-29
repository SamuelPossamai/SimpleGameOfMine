
#ifndef CONTROLLERS_HUMAN
#define CONTROLLERS_HUMAN

#include "unitcontroller.h"

namespace controller {

/*!
 * \brief Class that represents an human controller
 */
class Human : public UnitController {

protected:

    Human() : UnitController(false) {}

public:

    /*!
     * \brief Ask the user to choose a skill
     */
    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);

    /*!
     * \brief Ask the user to choose an angle
     */
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static Human *getController() { if(!_controller) _controller = new Human; return _controller; }

private:

    static Human *_controller;
};

} /* namespace Controllers */

#endif // CONTROLLERS_HUMAN
