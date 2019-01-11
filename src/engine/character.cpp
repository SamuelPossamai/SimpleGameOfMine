
#include <iostream>
#include <fstream>
#include <sstream>

#include <config/sgomfiles.h>

#include "character.h"

Character::Character(std::string char_name) : _name(char_name), _char_class("jobless"), _level(0),
    _experience(0), _attr({}) {

    auto opt = SGOMFiles::readSGOMDataFile(SGOMFiles::get()->charFilePath(char_name));

    if(!opt) return;

    for(auto& p : *opt) {

        const std::string& section_name = p.first;

        if(section_name == "General") {

            auto& job = p.second["job"];

            if(!job.empty()) _char_class = job;

            auto level = _get_int(p.second["level"]);

            if(level) _level = *level;

            auto xp = _get_int(p.second["xp"]);

            if(xp) _experience = *xp;
        }
        else if(section_name == "Attributes") {

            auto str = _get_int(p.second["STR"]);
            if(str) _attr.setStrength(*str);

            auto vit = _get_int(p.second["VIT"]);
            if(vit) _attr.setVitality(*vit);

            auto agi = _get_int(p.second["AGI"]);
            if(agi) _attr.setAgility(*agi);

            auto dex = _get_int(p.second["DEX"]);
            if(dex) _attr.setDexterity(*dex);

            auto wis = _get_int(p.second["WIS"]);
            if(wis)  _attr.setWisdom(*wis);
        }
        else if(section_name == "Items") _load_items(p.second);
    }

    _calculate_free_points_and_experience();
}

Character Character::newChar(std::string name, std::string job) {

    Character c(name);

    c._char_class = job;
    c.save();

    return c;
}

void Character::save() const {

    SGOMFiles::DataFileInfo info;

    info.emplace_back("General", SGOMFiles::DataFileInfo::value_type::second_type());

    info.back().second["level"] = std::to_string(_level);
    info.back().second["xp"] = std::to_string(_experience);
    info.back().second["job"] = _char_class;

    info.emplace_back("Attributes", SGOMFiles::DataFileInfo::value_type::second_type());

    info.back().second["STR"] = std::to_string(_attr.strength());
    info.back().second["VIT"] = std::to_string(_attr.vitality());
    info.back().second["AGI"] = std::to_string(_attr.agility());
    info.back().second["WIS"] = std::to_string(_attr.wisdom());
    info.back().second["DEX"] = std::to_string(_attr.dexterity());

    info.emplace_back("Items", SGOMFiles::DataFileInfo::value_type::second_type());

    for(auto& item : _items) {

        info.back().second[item.first] = std::to_string(item.second);
    }

    SGOMFiles::writeSGOMDataFile(SGOMFiles::get()->charFilePath(_name), info);
}

UIntegerType Character::remItem(const std::string& type, UIntegerType qtd /* = 1 */) {

    auto it = _items.find(type);
    if(it == _items.end()) return 0;

    UIntegerType ret = qtd;
    if(it->second > qtd) it->second -= qtd;
    else {
        ret = it->second;
        _items.erase(it);
    }

    return ret;
}

void Character::_load_items(const std::map<std::string, std::string>& items) {

    for(auto& item : items){

        const std::string& item_type = item.first;
        const std::string& item_qtd_s = item.second;

        auto item_qtd_val = _get_int(item_qtd_s);

        if(!item_qtd_val) {

            std::cerr << "Reading character file found '" << item_type <<
                         "' item info with invalid quantity value '" <<
                         item_qtd_s << "' for character '" <<
                         _name << "'." << std::endl;
            continue;
        }

        _items[item_type] = *item_qtd_val;
    }
}

void Character::_calculate_free_points_and_experience() {

    UIntegerType needed;

    while((needed = experienceNeeded()) <= experience()) {

        _experience -= needed;
        _level++;
    }

    UIntegerType attr_count = 0;
    for(UIntegerType i = 0; i < Attributes::statsCount(); i++) attr_count += _attr.getAttributeValue(i);

    UIntegerType total_points = _level*freePointsPerLevel();
    _free_points = total_points >= attr_count ? total_points - attr_count : 0;
}

std::optional<UIntegerType> Character::_get_int(const std::string& s) {

    if(s.empty()) return std::nullopt;

    std::istringstream ss(s);

    UIntegerType value;

    ss >> value;

    if(ss.eof() && !ss.fail() && !ss.bad()) return value;

    return std::nullopt;
}
