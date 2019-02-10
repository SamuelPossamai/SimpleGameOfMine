
#ifndef ACTIONSHANDLER_H
#define ACTIONSHANDLER_H

#include "skills/action.h"

class ActionsHandler {

    struct ActionElement;

public:

    using ActInfo = Action::ActInfo;
    using SkillInfo = Action::SkillInfo;
    using ProjectileCreationInterface = Action::ProjectileCreationInterface;

    ActionsHandler(const std::vector<std::pair<Action *, ActInfo> >& actions) {

        _actions.reserve(actions.size());

        for(auto& p : actions) {

            _actions.push_back({ p.first, p.first->firstAct(p.second), p.second });
            p.first->configActInfo(_actions.back().act_info);
        }
    }

    void callAct(Unit *u, EngineMap *m, ProjectileCreationInterface& pci,
                 const SkillInfo& s_info, const ActInfo& a_info) {

        for(auto& a : _actions) {

            if(a.next_step == s_info.step) a.next_step += a.action->act(u, m, pci, s_info, a_info);
        }
    }

    void reset() { for(auto& a : _actions) a.next_step = 0; }

private:

    struct ActionElement {

        Action *action;
        UIntegerType next_step;
        ActInfo act_info;
    };

    std::vector<ActionElement> _actions;
};

#endif // ACTIONSHANDLER_H
