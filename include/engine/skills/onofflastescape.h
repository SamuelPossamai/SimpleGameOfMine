
#ifndef ONOFFLASTESCAPE_H
#define ONOFFLASTESCAPE_H

#include "unitskill.h"

namespace skill {

class OnOffLastEscape : public UnitSkill {

protected:

    OnOffLastEscape() : UnitSkill(false) {}

public:

    virtual UIntegerType action(Unit *, Map *, const Info&) override;

    static OnOffLastEscape *getSkill() {

        if(!_skill) _skill =  new OnOffLastEscape;

        return _skill;
    }

private:

    static OnOffLastEscape *_skill;
};

} /* namespace skill */


#endif // ONOFFLASTESCAPE_H
