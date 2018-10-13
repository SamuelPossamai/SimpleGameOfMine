
#ifndef GAMEINFO_JOBS_H
#define GAMEINFO_JOBS_H

#include <optional>
#include <tuple>

#include <engine/unitsinfo/unitclassinfo.h>

namespace gameinfo {

class Jobs {

public:

    using Info = std::tuple<unitsinfo::UnitClassInfo *, UnitAnimationItemFactory *>;
    using Attributes = unitsinfo::UnitClassInfo::Attributes;

    static std::optional<Info> get(std::string name, const Attributes& attr);

private:

    using GetJobFunctionType = Info (*)(const Attributes&);

    static void _init();

    static std::map<std::string, GetJobFunctionType> _jobs;
};

} /* namespace gameinfo */

#endif // GAMEINFO_JOBS_H
