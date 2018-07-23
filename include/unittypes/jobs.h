
#ifndef JOBS_H
#define JOBS_H

#include <tuple>

#include <engine/unitsinfo/unitclassinfo.h>

class Jobs {

public:

    using Info = std::tuple<unitsinfo::UnitClassInfo *, UnitAnimationItemFactory *>;
    using Attributes = unitsinfo::UnitClassInfo::Attributes;

    static Info get(std::string name, const Attributes& attr);
};

#endif // JOBS_H
