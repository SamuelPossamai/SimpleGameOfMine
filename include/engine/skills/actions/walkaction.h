
#ifndef ACTIONS_WALKACTION_H
#define ACTIONS_WALKACTION_H

#include <iostream>

#include "skills/action.h"

class WalkAction : public Action {

public:

    WalkAction() = default;
    virtual ~WalkAction() = default;

    virtual void configActInfo(ActInfo& a_info) {

        auto& is_ok = ( a_info["is_ok"] = true );

        configActDefaultsTo(a_info, "start", Variant::Integer(0));
        configActDefaultsTo(a_info, "duration", Variant::Integer(20));
        configActDefaultsTo(a_info, "distance", Variant::Integer(10));
        configActDefaultsTo(a_info, "relative_angle", true);
        configActDefaultsTo(a_info, "angle", Variant::Integer(10));

        auto&& start = a_info["start"];
        auto&& duration = a_info["duration"];
        auto&& distance = a_info["distance"];
        auto&& relative_angle = a_info["relative_angle"];
        auto&& angle = a_info["angle"];

        if(!start.isNumber()) _wrong_type(is_ok, "start");
        else start.numberToInteger();

        if(!duration.isNumber()) _wrong_type(is_ok, "duration");
        else duration.numberToInteger();

        if(!distance.isNumber()) _wrong_type(is_ok, "distance");
        else start.numberToReal();

        if(!relative_angle.isBool()) _wrong_type(is_ok, "relative_angle");

        if(!angle.isNumber()) _wrong_type(is_ok, "angle");
        else start.numberToReal();
    }

    virtual UIntegerType firstAct(const ActInfo&) = 0;

protected:

    void _wrong_type(Variant& is_ok, const char *attr) {

        std::cerr << "walk action: Wrong type for '" << attr << "'" << std::endl;
        is_ok = false;
    }
};

#endif // ACTIONS_WALKACTION_H
