
#ifndef UNITSINFO_SLIME_H
#define UNITSINFO_SLIME_H

#include "unitinfo.h"

namespace unitsinfo {

class Slime : public UnitInfo {

public:

    static Slime *getInfo();

private:

    static Slime *_info;
};

} /* namespace creature */

#endif // UNITSINFO_SLIME_H
