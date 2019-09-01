
#ifndef GAMEINFO_JOBS_H
#define GAMEINFO_JOBS_H

#include <optional>
#include <tuple>

#include "unitinfo.h"

namespace gameinfo {

class Jobs {

public:

    using Info = std::tuple<UnitInfo *, UnitAnimationItemFactory *>;

    static std::optional<Info> get(const std::string& name);

private:

    using GetJobFunctionType = Info (*)();

    static void _init();

    static std::map<std::string, GetJobFunctionType> _jobs;
};

} /* namespace gameinfo */

#endif // GAMEINFO_JOBS_H
