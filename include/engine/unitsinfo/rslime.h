
#ifndef UNITSINFO_RSLIME_H
#define UNITSINFO_RSLIME_H

#include "unitsinfo/slime.h"

namespace unitsinfo {

class RSlime : public Slime {

public:

    virtual void init(Unit *u) const override;

    static RSlime *getInfo();

private:

    static RSlime *_info;
};

} /* namespace unitsinfo */

#endif // UNITSINFO_RSLIME_H
