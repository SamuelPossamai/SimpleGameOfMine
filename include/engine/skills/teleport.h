
#ifndef SKILLS_TELEPORT_H
#define SKILLS_TELEPORT_H

#include <engine/unitskill.h>

namespace skill {

class Teleport : public UnitSkill {

protected:

    Teleport() : UnitSkill(false) {}

public:

    virtual UIntegerType action(Unit *, Map *, const Info&) override;

    static Teleport *getSkill() {

        if(!_skill) _skill =  new Teleport;

        return _skill;
    }

    static void teleportUnit(Unit *u);

private:

    static Teleport *_skill;

};

} /* namespace skill */

#endif // SKILLS_TELEPORT_H
