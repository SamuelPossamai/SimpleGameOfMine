
#include <iostream>

#include <variantdatainfo.h>

#include "unit.h"
#include "skills/walk.h"
#include "engine/skills/actions/walkaction.h"

static WalkAction _action;

static struct { struct Init {

    Init() { Action::addAction("walk", &_action); }

} _; } __init;

namespace ainfoconfig = sutils::variantdatainfo;

void WalkAction::configActInfo(ActInfo& a_info) {

    auto& is_ok = ( a_info["is_ok"] = true );

    auto&& start = ainfoconfig::defaultsTo(a_info, "start", 0).first;
    auto&& duration = ainfoconfig::defaultsTo(a_info, "duration", 20).first;
    auto&& distance = ainfoconfig::defaultsTo(a_info, "distance", 10).first;
    auto&& set_angle = ainfoconfig::defaultsTo(
                a_info, "set_angle", false).first;
    auto&& angle_relative_to_chosen = ainfoconfig::defaultsTo(
                a_info, "angle_relative_to_chosen", false).first;
    auto&& angle_relative_to_char = ainfoconfig::defaultsTo(
                a_info, "angle_relative_to_char",
                !bool(angle_relative_to_chosen->second)).first;
    auto&& angle = ainfoconfig::defaultsTo(a_info, "angle", 10).first;

    if(!start->second.isNumber()) _wrong_type(is_ok, "start");
    else start->second.numberToInteger();

    if(!duration->second.isNumber()) _wrong_type(is_ok, "duration");
    else duration->second.numberToInteger();

    if(!distance->second.isNumber()) _wrong_type(is_ok, "distance");
    else distance->second.numberToInteger();

    a_info["__ds__"] = 10*RealType(distance->second.get<Variant::Integer>())
            / duration->second.get<Variant::Integer>();

    if(!ainfoconfig::isType<bool>(angle_relative_to_char)) {

        _wrong_type(is_ok, "angle_relative_to_char");
    }

    if(!ainfoconfig::isType<bool>(angle_relative_to_chosen)) {

        _wrong_type(is_ok, "angle_relative_to_chosen");
    }

    if(!ainfoconfig::isType<bool>(set_angle)) {

        _wrong_type(is_ok, "set_angle");
    }

    if(is_ok) {

        if(bool(angle_relative_to_char->second) &&
                bool(angle_relative_to_chosen->second)) {

            std::cerr << "walk action: both 'angle_relative_to_char' and "
                         "'angle_relative_to_chosen' were set, assuming "
                         "'angle_relative_to_char'" << std::endl;
            angle_relative_to_chosen->second = false;
        }
    }

    if(angle->second.isNumber()) {

        angle->second = -M_PI*Variant::Real(angle->second)/180;
    }
    else _wrong_type(is_ok, "angle");

    a_info["__angle_calcd__"] = false;
}

UIntegerType WalkAction::firstAct(const ActInfo& a_info) {

    return UIntegerType(a_info.find("start")->second.get<Variant::Integer>());
}

bool WalkAction::needAngle(const ActInfo& a_info) {

    return a_info.find("angle_relative_to_chosen")->second.get<bool>();
}

UIntegerType WalkAction::act(Unit *u, EngineMap *, ProjectileCreationInterface&,
                             const SkillInfo& i, ActInfo& a) {

    const auto start =
            UIntegerType(a.find("start")->second.get<Variant::Integer>());

    if(i.step < start) return start - i.step;

    decltype(i.angle) angle;

    if(!a.find("__angle_calcd__")->second.get<bool>()) {

        angle = a.find("angle")->second.getNumber();

        if(a.find("angle_relative_to_char")->second.get<bool>()) {

            angle += u->angle();
        }
        else if(a.find("angle_relative_to_chosen")->second.get<bool>()) {

            angle += i.angle;
        }

        if(a.find("set_angle")->second.get<bool>()) u->setAngle(angle);

        a["__angle__"] = Variant::Real(angle);
        a["__angle_calcd__"] = true;
    }
    else angle = a.find("__angle__")->second.getNumber();


    const auto duration =
            UIntegerType(a.find("duration")->second.get<Variant::Integer>());

    const auto ds =
            UIntegerType(a.find("__ds__")->second.getNumber());

    auto ret = skill::Walk::walk(u, i.step - start,
                                 1 + ((duration - 1) / 3), ds, angle);

    if(ret == 0) a["__angle_calcd__"] = false;

    return ret;
}

void WalkAction::_wrong_type(Variant& is_ok, const char *attr) {

    std::cerr << "walk action: Wrong type for '" << attr << "'" << std::endl;
    is_ok = false;
}
