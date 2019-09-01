
#ifndef BASICUNITGRAPHICITEMMAPPED_H
#define BASICUNITGRAPHICITEMMAPPED_H

#include "basicunitgraphicitem.h"

namespace unitanimation {

class BasicUnitGraphicItemMapped : public BasicUnitGraphicItem {

public:

    BasicUnitGraphicItemMapped(Unit *u) : BasicUnitGraphicItem(u) {}

    virtual ~BasicUnitGraphicItemMapped() override;

    virtual bool redraw() override {

        bool result = BasicUnitGraphicItem::redraw();

        if(!result) return false;

        if(_next_animation_id < animationsAmount()) {
            selectAnimation(_next_animation_id);
            _next_animation_id = animationsAmount();
        }

        return true;
    }

    template <typename... Animations>
    void setAnimations(const Animation&, Animations&&...) = delete;

    template <typename... Animations>
    void addAnimations(const Animation&, Animations&&...) = delete;

    template <typename InputIterator>
    void addAnimations(const Animation& animation, InputIterator begin, InputIterator end) {

        UIntegerType animation_id = animationsAmount();

        BasicUnitGraphicItem::addAnimations(animation);

        for(; begin != end; begin++) {
            _skill_animation_map[*begin] = animation_id;
        }
    }

    void addAnimation(const Animation& animation, std::string skill_name) {

        UIntegerType animation_id = animationsAmount();

        BasicUnitGraphicItem::addAnimations(animation);

        _skill_animation_map[skill_name] = animation_id;
    }

protected:

    virtual void unitSkillStarted(const Unit *u) override {

        auto it = _skill_animation_map.find(u->skillName());

        if(it == _skill_animation_map.end()) {

            _next_animation_id = 0;
        }
        else{

            _next_animation_id = it->second;
        }
    }

    virtual void unitSkillFinished(const Unit *) override { _next_animation_id = 0; }

private:

    UIntegerType _next_animation_id;
    std::map<std::string, UIntegerType> _skill_animation_map;
};

} /* namespace unitanimation */

#endif // BASICUNITGRAPHICITEMMAPPED_H
