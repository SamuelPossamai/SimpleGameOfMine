
#ifndef GAMEINFO_CREATURES_H
#define GAMEINFO_CREATURES_H

#include <map>
#include <tuple>
#include <vector>
#include <optional>

#include <config/types.h>

#include "utility/random.h"
#include "utility/iteratorwrapper.h"

namespace gameinfo {

class Creatures {

public:

    struct Info;

private:

    using GetCreatureFunctionType = Info (*)();
    using CreaturesInfoContainer = std::map<std::string, GetCreatureFunctionType>;

    struct CallGetZero {

        auto operator()(const CreaturesInfoContainer::value_type& val) -> decltype(std::get<0>(val)) { return std::get<0>(val); }
    };

public:

    using DropItemsType = std::vector<std::pair<std::string, RealType> >;

    /*!
     * \brief Struct with the information about a creature
     */
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

    Creatures() { if(_creatures.empty()) _init(); }

    /*!
     * \brief Access information of a creature type
     * \param name Name of the creature type
     * \return std::optional with the information about the creature if it exists
     */
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

    /*!
     * \brief Return an iterator to the begin of a list of the creature type names
     * \return iterator the the begin of a list of the creature type names
     */
    utility::IteratorWrapper<CreaturesInfoContainer::const_iterator, CallGetZero> begin() const { return _creatures.cbegin(); }

    /*!
     * \brief Return an iterator to the end of a list of the creature type names
     * \return iterator the the end of a list of the creature type names
     */
    utility::IteratorWrapper<CreaturesInfoContainer::const_iterator, CallGetZero> end() const { return _creatures.cend(); }

private:

    static void _init();

    static void _get_items(std::vector<std::string>& out, const std::string& creature) {

        auto opt = get(creature);
        if(!opt) return;
        xGetItems(out, opt->dropItems);
    }

    static void _get_items(std::vector<std::string>& out, const DropItemsType& drops) {

        for(auto&& drop : drops) if(utility::Random::chance(drop.second)) out.push_back(drop.first);
    }

    static CreaturesInfoContainer _creatures;
};

} /* namespace gameinfo */

#endif // GAMEINFO_CREATURES_H
