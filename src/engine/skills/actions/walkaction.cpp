
#include <iostream>

#include <variantdatainfo.h>

#include "unit.h"
#include "skills/walk.h"
#include "engine/skills/actions/walkaction.h"

namespace ainfoconfig = sutils::variantdatainfo;

void WalkAction::configActInfo(ActInfo& a_info) {

    auto& is_ok = ( a_info["is_ok"] = true );

    auto&& start = ainfoconfig::defaultsTo(a_info, "start", 0).first;
    auto&& duration = ainfoconfig::defaultsTo(a_info, "duration", 20).first;
    auto&& distance = ainfoconfig::defaultsTo(a_info, "distance", 10).first;
    auto&& angle_relative_to_char = ainfoconfig::defaultsTo(a_info, "angle_relative_to_char", true).first;
    auto&& angle_relative_to_chosen = ainfoconfig::defaultsTo(a_info, "angle_relative_to_chosen", true).first;
    auto&& angle = ainfoconfig::defaultsTo(a_info, "angle", 10).first;

    if(!start->second.isNumber()) _wrong_type(is_ok, "start");
    else start->second.numberToInteger();

    if(!duration->second.isNumber()) _wrong_type(is_ok, "duration");
    else duration->second.numberToInteger();

    if(!distance->second.isNumber()) _wrong_type(is_ok, "distance");
    else distance->second.numberToInteger();

    a_info["__ds__"] = RealType(distance->second.get<Variant::Integer>()) / duration->second.get<Variant::Integer>();

    if(!ainfoconfig::isType<bool>(angle_relative_to_char)) _wrong_type(is_ok, "angle_relative_to_char");

    if(!ainfoconfig::isType<bool>(angle_relative_to_chosen)) _wrong_type(is_ok, "angle_relative_to_chosen");

    if(is_ok) {

        if(bool(angle_relative_to_char->second) && bool(angle_relative_to_chosen->second)) {

            std::cerr << "walk action: both 'angle_relative_to_char' and 'angle_relative_to_chosen'"
                         " were set, assuming 'angle_relative_to_char'" << std::endl;
            angle_relative_to_chosen->second = false;
        }
    }

    if(!ainfoconfig::numberToReal(angle)) _wrong_type(is_ok, "angle");
}

UIntegerType WalkAction::firstAct(const ActInfo& a_info) {

    return UIntegerType(a_info.find("start")->second.get<Variant::Integer>());
}

UIntegerType WalkAction::act(Unit *u, EngineMap *, ProjectileCreationInterface&, const SkillInfo& i, const ActInfo& a) {

    auto angle = i.angle;

    angle += a.find("angle")->second.getNumber();

    if(a.find("angle_relative_to_char")->second.get<bool>()) angle += u->angle();

    return skill::Walk::walk(u, i.step, UIntegerType(a.find("duration")->second.get<Variant::Integer>()),
                             UIntegerType(a.find("__ds__")->second.getNumber()), angle);
}

void WalkAction::_wrong_type(Variant& is_ok, const char *attr) {

    std::cerr << "walk action: Wrong type for '" << attr << "'" << std::endl;
    is_ok = false;
}
