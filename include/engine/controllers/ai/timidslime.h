
#ifndef CONTROLLERS_TIMIDSLIME_H
#define CONTROLLERS_TIMIDSLIME_H

#include "controllers/ai/slime.h"

namespace controller {

namespace AI {

class TimidSlime : public Slime {

    TimidSlime() {}

public:

    virtual std::optional<AngleType> chooseAngle(const Unit *, const Map *, UserInterface *);

    static TimidSlime *getController() { if(!_controller) _controller = new TimidSlime; return _controller; }

private:

    static TimidSlime *_controller;


};

} /* namespace controller */

} /* namespace AI */

#endif // TIMIDSLIME_H
