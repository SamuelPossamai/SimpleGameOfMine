
#ifndef UNITSINFO_FIGHTER_H
#define UNITSINFO_FIGHTER_H

#include "unitinfo.h"

namespace unitsinfo {

class Fighter : public UnitInfo {

public:

    static Fighter *getInfo();

private:

    static Fighter *_info;
};

} /* namespace creature */

#endif // UNITSINFO_FIGHTER_H
