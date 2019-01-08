
#ifndef GAMEINFO_CREATURES_H
#define GAMEINFO_CREATURES_H

#include <map>
#include <tuple>
#include <optional>

#include <config/types.h>

namespace gameinfo {

class Creatures {

public:

    using Info = std::tuple<UnitInfo *, UnitAnimationItemFactory *, UnitController *>;

    static std::optional<Info> get(const std::string& name);

private:

    using GetCreatureFunctionType = Info (*)();

    static void _init();

    static std::map<std::string, GetCreatureFunctionType> _creatures;
};

} /* namespace gameinfo */

#endif // GAMEINFO_CREATURES_H
