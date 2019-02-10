
#ifndef SKILLS_ACTIONSSEQUECESKILL_H
#define SKILLS_ACTIONSSEQUECESKILL_H

#include "unitskill.h"
#include "actionshandler.h"

namespace skill {

class ActionsSequeceSkill : public UnitSkill {

public:

    using ActInfo = Action::ActInfo;

    ActionsSequeceSkill(bool need_angle, const std::vector<std::pair<Action *, ActInfo> >& actions) :
        UnitSkill(need_angle), _actions(actions) {}

private:

    ActionsHandler _actions;
};

} /* namespace skill */

#endif // SKILLS_ACTIONSSEQUECESKILL_H
