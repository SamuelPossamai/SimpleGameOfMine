
#include <iostream>

#include "selectuserinterfacebase.h"
#include "selectuserinterface.h"
#include "characterselectionscreen.h"
#include "sgomfiles.h"

SelectUserInterfaceBase *SelectUserInterfaceBase::create(const utility::Interval<UIntegerType>& n_characters) {

    auto info = SGOMFiles::get()->readSGOMConfigFile();

    auto *created = _create(n_characters, info["Character Selection Screen"]["mode"]);

    if(created) return created;

    std::cerr << "Option selected in configuration file does not match "
                 "any character selection screen mode, so default will be used" << std::endl;

    return _create(n_characters, SGOMFiles::readSGOMDefaultConfigFile()["Character Selection Screen"]["mode"]);
}

SelectUserInterfaceBase *SelectUserInterfaceBase::_create(const utility::Interval<UIntegerType>& n_characters,
                                                          const SGOMFiles::Variant& mode) {

    if(!mode.isString()) return nullptr;

    if(mode == "Table") return new SelectUserInterface(n_characters);
    else if(mode == "Visual") return new CharacterSelectionScreen(n_characters);

    return nullptr;
}
