
#include <iostream>

#include "engine/skills/actionssequeceskill.h"

using namespace skill;

ActionsSequeceSkill::~ActionsSequeceSkill() {
}

UnitSkill *ActionsSequeceSkill::create(const sutils::VariantDataInfo& data_info) {

    auto&& name_it = data_info.find("name");

    std::string name;

    if(name_it == data_info.end()) name = "<<nameless>>";
    else {

        if(name_it->second.isString())  {

            name = name_it->second.get<sutils::Variant::String>();
        }
        else name = "<<invalid>>";
    }

    auto&& actions_it = data_info.find("action");

    if(actions_it == data_info.end()) {

        std::cerr << "Failed to load '" << name <<
                     "' action sequence skill: \"No 'actions' field\"." << std::endl;
        return nullptr;
    }

    if(!actions_it->second.isList()) {

        std::cerr << "Failed to load '" << name <<
                     "' action sequence skill: \"Invalid 'actions' "
                     "field, must be a list\"." << std::endl;
        return nullptr;
    }

    auto& actions = actions_it->second.get<sutils::Variant::List>();

    std::vector<std::pair<Action *, ActInfo> > actions_arg;

    actions_arg.reserve(actions.size());
    for(auto&& action : actions) {

        if(!action.isMap()) {

            std::cerr << "Failed to load action for '" << name << "': Cannot interpret '"
                      << action << "'" << std::endl;

            return nullptr;
        }

        auto&& action_map = action.get<sutils::Variant::Map>();

        auto&& type_it = action_map.find("type");

        if(type_it == action_map.end()) {

            std::cerr << "Failed to load action for '" << name <<
                         "': Missing action type" << std::endl;
            return nullptr;
        }

        if(!type_it->second.isString()) {

            std::cerr << "Failed to load action for '" << name <<
                         "': Invalid action type '" << type_it->second.type() << "'" << std::endl;
            return nullptr;
        }

        auto&& action_name = type_it->second.get<sutils::Variant::String>();
        auto *action_type = Action::getAction(action_name);

        if(action_type == nullptr) {

            std::cerr << "Failed to load action for '" << name <<
                         "': No action type named '" << action_name << "'" << std::endl;
            return nullptr;
        }

        auto&& info_it = action_map.find("info");

        if(info_it == action_map.end()) {

            std::cerr << "Failed to load action for '" << name <<
                         "': Missing action info" << std::endl;
            return nullptr;
        }

        if(!info_it->second.isMap()) {

            std::cerr << "Failed to load action for '" << name <<
                         "': Invalid action info '" << type_it->second.type() << "'" << std::endl;
            return nullptr;
        }

        sutils::VariantDataInfo data_info;

        for(auto p : info_it->second.get<sutils::Variant::Map>()) {

            if(p.first.isString()) {

                data_info.insert({p.first.get<sutils::Variant::String>(), p.second});
            }
            else {

                std::cerr << "Failed to load action for '" << name <<
                             "': Action info with key of type different than 'String'" << std::endl;
                return nullptr;
            }
        }

        actions_arg.emplace_back(action_type, data_info);
    }

    return new ActionsSequeceSkill(actions_arg);
}
