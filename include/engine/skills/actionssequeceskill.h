
#ifndef SKILLS_ACTIONSSEQUECESKILL_H
#define SKILLS_ACTIONSSEQUECESKILL_H

#include "unitskill.h"
#include "actionshandler.h"

namespace skill {

class ActionsSequeceSkill : public UnitSkill {

public:

    using ActInfo = Action::ActInfo;
    using ActionsList = std::vector<std::pair<Action *, ActInfo> >;

    ActionsSequeceSkill(const ActionsList& actions) : _actions(actions) {

        UnitSkill::setInputType(UnitSkill::InputType::angle,
                                _actions.needAngle());
    }

    virtual ~ActionsSequeceSkill() override;

    virtual UIntegerType action(Unit *u, EngineMap *m,
                                ProjectileCreationInterface& pci,
                                const Info& info) override {

        if(info.step == 0) _actions.reset();

        _actions.callAct(u, m, pci, info);

        return _actions.finished() ? 0 : 1;
    }

    static UnitSkill *create(const sutils::VariantDataInfo& data_info);

    virtual void destroy() override { delete this; }

private:

    ActionsHandler _actions;
};

} /* namespace skill */

#endif // SKILLS_ACTIONSSEQUECESKILL_H
