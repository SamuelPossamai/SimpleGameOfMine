
#include <gameinfo/items.h>

using namespace gameinfo;

std::map<std::string, Items::GetItemFunctionType> Items::_items;

std::optional<Items::Info> Items::get(const std::string& name) {

    if(_items.empty()) _init();

    auto func_it = _items.find(name);

    if(func_it == _items.end()) return std::nullopt;

    return (func_it->second)(name);
}

static Items::Info _get_arrow(const std::string&) {

    return Items::Info{QImage(":/arrow_projectile_image.png"), "Some say archers shoot these things over enemies"};
}

static Items::Info _get_sword(const std::string&) {

    return Items::Info{QImage(":/sword_image.png"), "Just a sword"};
}

static Items::Info _get_shuriken(const std::string&) {

    return Items::Info{QImage(":/shuriken_image.png"), "Are you trying to be a ninja or are you one already?"};
}

static Items::Info _get_green_ball(const std::string&) {

    return Items::Info{QImage(":/green_circle.png"), "Why?"};
}

void Items::_init() {

    _items["arrow"] = _get_arrow;
    _items["sword"] = _get_sword;
    _items["shuriken"] = _get_shuriken;
    _items["green_ball"] = _get_green_ball;
}
