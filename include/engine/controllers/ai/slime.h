
#ifndef CONTROLLERS_AI_SLIME_H
#define CONTROLLERS_AI_SLIME_H

#include "unitcontroller.h"

namespace controller {

namespace AI {

/*!
 * \brief Basic AI for slime creatures
 */
class Slime : public UnitController {

protected:

    Slime() {}

public:

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static Slime *getController() { if(!_controller) _controller = new Slime; return _controller; }

private:

    bool _angle_test(const Unit *u1, const Unit *u2) const;

    static Slime *_controller;
};

} /* namespace AI */

} /* namespace controller */

#endif // CONTROLLERS_AI_SLIME_H
