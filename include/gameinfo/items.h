
#ifndef GAMEINFO_ITEMS_H
#define GAMEINFO_ITEMS_H

#include <map>
#include <tuple>
#include <optional>

#include <QPixmap>

#include <config/types.h>

namespace gameinfo {

class Items {

public:

    using Info = std::tuple<QImage, std::string>;

    static std::optional<Info> get(const std::string& name);

private:

    using GetItemFunctionType = Info (*)(const std::string&);

    static void _init();

    static std::map<std::string, GetItemFunctionType> _items;
};

} /* namespace gameinfo */

#endif // GAMEINFO_ITEMS_H
