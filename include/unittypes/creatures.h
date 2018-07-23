
#ifndef CREATURES_H
#define CREATURES_H

#include <map>
#include <tuple>
#include <optional>

#include <config/types.h>

class Creatures {


public:

    using Info = std::tuple<UnitInfo *, UnitAnimationItemFactory *, UnitController *>;

    static std::optional<Info> get(std::string name, UIntegerType level);

private:

    using GetCreatureFunctionType = Info (*)(UIntegerType);

    static void _init();

    static std::map<std::string, GetCreatureFunctionType> _creatures;
};

#endif // CREATURES_H
