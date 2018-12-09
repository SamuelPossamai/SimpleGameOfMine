
#ifndef SKILLS_SHOOT_H
#define SKILLS_SHOOT_H

#include "unitskill.h"

namespace skill {

class Shoot : public UnitSkill {

public:

    Shoot(const std::string& projectile_type) : UnitSkill(true), _projectile_type(projectile_type) {}

    virtual UIntegerType action(Unit*, EngineMap*, ProjectileCreationInterface&, const Info&) override;

private:

    std::string _projectile_type;
};

} /* namespace skill */

#endif // SKILLS_SHOOT_H
