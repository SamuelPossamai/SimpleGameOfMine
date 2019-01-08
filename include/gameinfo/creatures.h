
#ifndef GAMEINFO_CREATURES_H
#define GAMEINFO_CREATURES_H

#include <map>
#include <tuple>
#include <vector>
#include <optional>

#include <config/types.h>

#include "utility/random.h"

namespace gameinfo {

class Creatures {

public:

    using DropItemsType = std::vector<std::pair<std::string, RealType> >;

    struct Info {

        Info(UnitInfo *uinfo, UnitAnimationItemFactory *uanfac, UnitController *uctrl,
             DropItemsType drops = {}) :
            unitInfo(uinfo), unitAnimationItemFactory(uanfac),
            unitController(uctrl), dropItems(drops) {}

        UnitInfo *unitInfo;
        UnitAnimationItemFactory *unitAnimationItemFactory;
        UnitController *unitController;
        DropItemsType dropItems;
    };

    static std::optional<Info> get(const std::string& name);

    template<typename... Args>
    static std::vector<std::string> getItems(Args&&... args) {

        std::vector<std::string> ret;
        xGetItems(ret, args...);
        return ret;
    }

    template<typename T, typename... Args>
    static void xGetItems(std::vector<std::string>& out, T&& arg, Args&&... args) {

        xGetItems(out, arg);
        xGetItems(out, args...);
    }

    template<typename T>
    static void xGetItems(std::vector<std::string>& out, T&& arg) { _get_items(out, arg); }

    static void xGetItems(std::vector<std::string>&) {}

private:

    using GetCreatureFunctionType = Info (*)();

    static void _init();

    static void _get_items(std::vector<std::string>& out, const std::string& creature) {

        auto opt = get(creature);
        if(!opt) return;
        xGetItems(out, opt->dropItems);
    }

    static void _get_items(std::vector<std::string>& out, const DropItemsType& drops) {

        for(auto&& drop : drops) if(utility::Random::chance(drop.second)) out.push_back(drop.first);
    }

    static std::map<std::string, GetCreatureFunctionType> _creatures;
};

} /* namespace gameinfo */

#endif // GAMEINFO_CREATURES_H
