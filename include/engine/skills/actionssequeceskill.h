
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

    virtual ~ActionsSequeceSkill() override;

    virtual UIntegerType action(Unit *u, EngineMap *m, ProjectileCreationInterface& pci,
                                const Info& info) override {

        _actions.callAct(u, m, pci, info);

        return _actions.finished(info) ? 0 : 1;
    }

    static UnitSkill *create(const utility::VariantDataInfo& data_info);

    virtual void destroy() override { delete this; }

private:

    ActionsHandler _actions;
};

} /* namespace skill */

#endif // SKILLS_ACTIONSSEQUECESKILL_H
