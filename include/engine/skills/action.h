
#ifndef ACTION_H
#define ACTION_H

#include "utility/variant.h"
#include "unitskill.h"

class Action {

public:

    using Variant = utility::Variant;
    using SkillInfo = UnitSkill::Info;
    using ActInfo = utility::VariantDataInfo;
    using ProjectileCreationInterface = UnitSkill::ProjectileCreationInterface;

    Action() = default;
    virtual ~Action() = default;

    virtual void configActInfo(ActInfo&) = 0;

    virtual UIntegerType firstAct(const ActInfo&) = 0;

    virtual UIntegerType act(Unit*, EngineMap*, ProjectileCreationInterface&,
                             const SkillInfo&, const ActInfo&) = 0;

    virtual bool needAngle(const ActInfo&) const = 0;

    virtual bool finished(const SkillInfo&, const ActInfo&) const = 0;

    static Action *getAction(const std::string& name) {

        if(!_actions) return nullptr;

        auto it = _actions->find(name);

        if(it == _actions->end()) return nullptr;

        return it->second;
    }

    static bool addAction(const std::string& name, Action *action) {

        _actions_init();

        auto it = _actions->find(name);

        if(it != _actions->end()) return false;

        _actions->insert({name, action});

        return true;
    }

    static bool remAction(const std::string& name) {

        if(!_actions) return false;

        auto it = _actions->find(name);

        if(it == _actions->end()) return false;

        _actions->erase(it);

        return true;
    }

private:

    using ActionsContainer = std::map<std::string, Action *>;

    static void _actions_init() { if(!_actions) _actions = new ActionsContainer; }

    static ActionsContainer *_actions;
};

#endif // ACTION_H
