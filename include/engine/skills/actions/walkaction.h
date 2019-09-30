
#ifndef ACTIONS_WALKACTION_H
#define ACTIONS_WALKACTION_H

#include "skills/action.h"

class WalkAction : public Action {

public:

    WalkAction() = default;
    virtual ~WalkAction() override = default;

    virtual void configActInfo(ActInfo& a_info) override;
    virtual UIntegerType firstAct(const ActInfo&) override;

    virtual UIntegerType act(Unit*, EngineMap*, ProjectileCreationInterface&,
                             const SkillInfo&, ActInfo&) override;

    virtual bool needAngle(const ActInfo&) override;

protected:

    static void _wrong_type(Variant& is_ok, const char *attr);
};

#endif // ACTIONS_WALKACTION_H
