
#ifndef GAMEINFO_SKILLS_H
#define GAMEINFO_SKILLS_H

#include <map>
#include <tuple>
#include <vector>
#include <optional>

#include <QPixmap>

#include "config/types.h"
#include "utility/iteratorwrapper.h"

namespace gameinfo {

class Skills {

public:

    struct Info;

private:

    using GetSkillFunctionType = Info (*)();
    using SkillsInfoContainer = std::map<std::string, GetSkillFunctionType>;

    struct CallGetZero {

        auto operator()(const SkillsInfoContainer::value_type& val) -> decltype(std::get<0>(val)) { return std::get<0>(val); }
    };

public:

    using iterator = utility::IteratorWrapper<SkillsInfoContainer::const_iterator, CallGetZero>;

    /*!
     * \brief Struct with the information about a skill
     */
    struct Info {

        Info(UnitSkillFactory *f, const QPixmap& p = QPixmap()) : factory(f), icon(p) {}

        UnitSkillFactory *factory;
        QPixmap icon;
    };

    Skills() { if(_skills.empty()) _init(); }
    ~Skills() = default;

    /*!
     * \brief Access information of a skill and create a skilly
     * \param name Name of the skill
     * \return std::optional with the information about the skill if it exists
     */
    static std::optional<Info> get(const std::string& name);

    /*!
     * \brief Return an iterator to the begin of a list of the skill names
     * \return iterator the the begin of a list of the skill names
     */
    iterator begin() const { return _skills.cbegin(); }

    /*!
     * \brief Return an iterator to the end of a list of the skill names
     * \return iterator the the end of a list of the skill names
     */
    iterator end() const { return _skills.cend(); }

private:

    static void _init();

    static SkillsInfoContainer _skills;
};

} /* namespace gameinfo */

#endif // GAMEINFO_SKILLS_H
