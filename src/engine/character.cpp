
#include <iostream>
#include <fstream>
#include <sstream>

#include "character.h"

Character::Character(std::string char_name) : _name(char_name), _char_class("jobless"), _level(0),
    _experience(0), _attr({}) {

    auto opt = SGOMFiles::readSGOMDataFile(SGOMFiles::get()->charFilePath(char_name));

    if(!opt) return;

    using Variant = SGOMFiles::Variant;

    for(auto& p : *opt) {

        const std::string& section_name = p.first;

        if(section_name == "General") {

            const Variant& job = p.second["job"];

            if(job.isString()) {

                auto job_v = job.get<Variant::String>();
                if(!job_v.empty()) _char_class = job_v;
            }
            else _type_error_message("General", "job", "String", Variant::typeName(job.typeId()), char_name.c_str());

            const Variant& level = p.second["level"];

            if(level.isInteger()) _level = UIntegerType(level.get<Variant::Integer>());
            else _type_error_message("General", "level", "Integer", Variant::typeName(level.typeId()), char_name.c_str());

            const Variant& xp = p.second["xp"];

            if(xp.isInteger()) _experience = UIntegerType(xp.get<Variant::Integer>());
            else _type_error_message("General", "xp", "Integer", Variant::typeName(xp.typeId()), char_name.c_str());
        }
        else if(section_name == "Attributes") {

            auto str = p.second["STR"];
            if(str.isInteger()) _attr.setStrength(UIntegerType(str.get<Variant::Integer>()));
            else _type_error_message("Attributes", "STR", "Integer", Variant::typeName(str.typeId()), char_name.c_str());

            auto vit = p.second["VIT"];
            if(vit.isInteger()) _attr.setVitality(UIntegerType(vit.get<Variant::Integer>()));
            else _type_error_message("Attributes", "VIT", "Integer", Variant::typeName(vit.typeId()), char_name.c_str());

            auto agi = p.second["AGI"];
            if(agi.isInteger()) _attr.setAgility(UIntegerType(agi.get<Variant::Integer>()));
            else _type_error_message("Attributes", "AGI", "Integer", Variant::typeName(agi.typeId()), char_name.c_str());

            auto dex = p.second["DEX"];
            if(dex.isInteger()) _attr.setDexterity(UIntegerType(dex.get<Variant::Integer>()));
            else _type_error_message("Attributes", "DEX", "Integer", Variant::typeName(dex.typeId()), char_name.c_str());

            auto wis = p.second["WIS"];
            if(wis.isInteger()) _attr.setWisdom(UIntegerType(wis.get<Variant::Integer>()));
            else _type_error_message("Attributes", "WIS", "Integer", Variant::typeName(wis.typeId()), char_name.c_str());
        }
        else if(section_name == "Items") _load_items(p.second, char_name.c_str());
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

    using Integer = SGOMFiles::Variant::Integer;

    info.back().second["level"] = Integer(_level);
    info.back().second["xp"] = Integer(_experience);
    info.back().second["job"] = _char_class;

    info.emplace_back("Attributes", SGOMFiles::DataFileInfo::value_type::second_type());

    info.back().second["STR"] = Integer(_attr.strength());
    info.back().second["VIT"] = Integer(_attr.vitality());
    info.back().second["AGI"] = Integer(_attr.agility());
    info.back().second["WIS"] = Integer(_attr.wisdom());
    info.back().second["DEX"] = Integer(_attr.dexterity());

    info.emplace_back("Items", SGOMFiles::DataFileInfo::value_type::second_type());

    for(auto& item : _items) {

        info.back().second[item.first] = Integer(item.second);
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

void Character::_load_items(const std::map<std::string, SGOMFiles::Variant>& items, const char *char_name) {

    using Variant = SGOMFiles::Variant;

    for(auto& item : items){

        const std::string& item_type = item.first;
        const SGOMFiles::Variant& item_qtd = item.second;

        if(!item_qtd.isInteger()) {

            _type_error_message("Items", item_type.c_str(), "Integer", Variant::typeName(item_qtd.typeId()), char_name);

            continue;
        }

        auto item_qtd_val = item_qtd.get<Variant::Integer>();

        if(item_qtd_val <= 0) {

            std::cerr << "Reading character file found '" << item_type <<
                         "' item info with invalid quantity value '" <<
                         item_qtd_val << "' for character '" <<
                         _name << "'." << std::endl;
            continue;
        }

        _items[item_type] = UIntegerType(item_qtd_val);
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

void Character::_type_error_message(const char *section, const char *data, const char *desired_type, const char *type, const char *name) {

    std::cerr<< '\'' << data << "' data at section '" << section <<
                "' must be a '" << desired_type << "' in '" << name <<
                "' character file but was '" << type << "'" << std::endl;
}
