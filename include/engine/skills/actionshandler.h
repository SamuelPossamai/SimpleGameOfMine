
#ifndef ACTIONSHANDLER_H
#define ACTIONSHANDLER_H

#include "skills/action.h"

class ActionsHandler {

public:

    using ActInfo = Action::ActInfo;
    using SkillInfo = Action::SkillInfo;
    using ProjectileCreationInterface = Action::ProjectileCreationInterface;

    ActionsHandler(const std::vector<Action *>& actions, ActInfo& a_info) {

        _actions.reserve(actions.size());

        for(Action *a : actions) {

            a->configActInfo(a_info);
            _actions.emplace_back(a, a->firstAct(a_info));
        }

    }

    UIntegerType callAct(Unit *u, EngineMap *m, ProjectileCreationInterface& pci,
                                 const SkillInfo& s_info, const ActInfo& a_info) {

        for(auto& p : _actions) {

            if(p.second == s_info.step) p.second += p.first->act(u, m, pci, s_info, a_info);
        }
    }

    void reset() { for(auto& p : _actions) p.second = 0; }

private:

    std::vector<std::pair<Action *, UIntegerType> > _actions;
};

#endif // ACTIONSHANDLER_H
