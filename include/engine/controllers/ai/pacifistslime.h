
#ifndef CONTROLLERS_PACIFISTSLIME_H
#define CONTROLLERS_PACIFISTSLIME_H

#include "controllers/ai/slime.h"

namespace controller {

namespace AI {

class PacifistSlime : public Slime {

protected:

    PacifistSlime() {}

public:

    virtual ~PacifistSlime() {}

    virtual UIntegerType chooseSkill(const Unit *, const Map *, UserInterface *);
    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    /*!
     * \brief Return a dynamically allocated copy of this class instance, if it is yet not created, create it
     * \return Object of this class
     */
    static PacifistSlime *getController() { if(!_controller) _controller = new PacifistSlime; return _controller; }

private:

    static PacifistSlime *_controller;
};

} /* namespace AI */

} /* namespace controller */

#endif // CONTROLLERS_PACIFISTSLIME_H
