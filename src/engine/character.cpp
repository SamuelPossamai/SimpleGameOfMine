
#include <fstream>

#include <config/sgomfiles.h>

#include "character.h"

Character::Character(std::string char_name) : _name(char_name), _char_class("jobless"), _free_points(0),
    _experience(0), _attr({}) {

    std::ifstream file(SGOMFiles::get()->charFilePath(char_name));

    std::getline(file, _char_class, '\n');

    for(UIntegerType i = 0; i < Attributes::statsCount(); i++) {

        file >> _attr.stats[i];
        file.ignore();
    }

    file >> _experience;
    file >> _free_points;

    _calculate_level();
    _calculate_free_points_and_experience();
}

Character Character::newChar(std::string name, std::string job) {

    Character c(name);

    c._char_class = job;
    c.save();

    return c;
}

void Character::save() const {

    std::ofstream file(SGOMFiles::get()->charFilePath(_name));

    file << _char_class << std::endl;

    for(UIntegerType i = 0; i < Attributes::statsCount(); i++) file << _attr.stats[i] << std::endl;

    file << _experience << std::endl;
    file << _free_points << std::endl;
}

void Character::_calculate_free_points_and_experience() {

    UIntegerType needed;

    while((needed = experienceNeeded()) <= experience()) {

        _experience -= needed;
        _free_points++;
        _level++;
    }
}

