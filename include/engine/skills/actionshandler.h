
#ifndef ACTIONSHANDLER_H
#define ACTIONSHANDLER_H

#include <limits>

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

            _actions.push_back({ p.first,
                                 p.first->firstAct(p.second), p.second });
            p.first->configActInfo(_actions.back().act_info);
        }
    }

    void callAct(Unit *u, EngineMap *m, ProjectileCreationInterface& pci,
                 const SkillInfo& s_info) {

        for(auto& a : _actions) {

            if(a.next_step == s_info.step) {

                UIntegerType after = a.action->act(u, m, pci,
                                                   s_info, a.act_info);
                if(after == 0) {
                    a.next_step = std::numeric_limits<UIntegerType>::max();
                }
                else a.next_step += after;
            }
        }
    }

    void reset() { for(auto& a : _actions) a.next_step = 0; }

    bool finished() const {

        for(auto& a_el : _actions) {

            if(a_el.next_step != std::numeric_limits<UIntegerType>::max()) {

                return false;
            }
        }

        return true;
    }

    bool needAngle() const {

        for(auto& a_el : _actions) {

            if(a_el.action->needAngle(a_el.act_info)) return true;
        }

        return false;
    }

private:

    struct ActionElement {

        Action *action;
        UIntegerType next_step;
        ActInfo act_info;
    };

    std::vector<ActionElement> _actions;
};

#endif // ACTIONSHANDLER_H
