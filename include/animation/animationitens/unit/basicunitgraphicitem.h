
#ifndef BASICUNITGRAPHICITEM_H
#define BASICUNITGRAPHICITEM_H

#include <typeindex>
#include <map>
#include <queue>

#include "animation/unitanimationitem.h"
#include "animatedobject.h"

namespace unitanimation {

class BasicUnitGraphicItem : public UnitAnimationItem {

    using EventQueue = std::queue<std::pair<void (BasicUnitGraphicItem::*)(const void *), const void *> >;

public:

    BasicUnitGraphicItem(Unit *u);

    virtual ~BasicUnitGraphicItem() override;

    virtual bool redraw() override {

        if(object() == nullptr) return false;

        while(!_events.empty()) {

            (this->*(_events.front().first))(_events.front().second);
            _events.pop();
        }

        return true;
    }

    template <typename... Animations>
    void setAnimations(const Animation& idle, Animations&&... skill_animations) {

        _obj->clearAnimations();
        _add_animations(idle, skill_animations...);
    }

protected:

    virtual void addToScene(QGraphicsScene *scene) override;

    virtual void removeFromScene() override;

    virtual void unitDeathEvent(Unit *) override { _events.push({ &BasicUnitGraphicItem::uDeathEvent, nullptr }); }
    virtual void unitSelected(Unit *) override { _events.push({ &BasicUnitGraphicItem::uSelected, nullptr }); }
    virtual void unitUnselected(Unit *) override { _events.push({ &BasicUnitGraphicItem::uUnselected, nullptr }); }
    virtual void engineObjectMoved(EngineObject *) override { _events.push({ &BasicUnitGraphicItem::uMoved, nullptr }); }
    virtual void engineObjectRotated(EngineObject *) override { _events.push({ &BasicUnitGraphicItem::uRotated, nullptr }); }
    virtual void unitSkillStarted(Unit *) override { _events.push({ &BasicUnitGraphicItem::uSkillStarted, nullptr }); }
    virtual void unitSkillFinished(Unit *) override { _events.push({ &BasicUnitGraphicItem::uSkillFinished, nullptr }); }
    virtual void unitSkillAdvance(Unit *) override { _events.push({ &BasicUnitGraphicItem::uSkillAdvance, nullptr }); }
    virtual void unitReceivedDamage(Unit *) override { _events.push({ &BasicUnitGraphicItem::uHealthChanged, nullptr }); }
    virtual void unitHealed(Unit *) override { _events.push({ &BasicUnitGraphicItem::uHealthChanged, nullptr }); }
    virtual void unitEnergyConsumed(Unit *) override {

        if(_energy_bar) _events.push({ &BasicUnitGraphicItem::uEnergyConsumed, nullptr });
    }
    virtual void unitSpecialChanged(Unit *) override {

        _events.push({ &BasicUnitGraphicItem::uSpecialChanged, nullptr });
    }
    virtual void unitRageChanged(Unit *) override {

        _events.push({ &BasicUnitGraphicItem::uRageChanged, nullptr });
    }
    virtual void unitEffectAdded(Unit *, const UnitEffect *e) override {

        _events.push({ &BasicUnitGraphicItem::uEffectAdded, static_cast<const void *>(e) });
    }
    virtual void unitEffectRemoved(Unit *, const UnitEffect *e) override {

        _events.push({ &BasicUnitGraphicItem::uEffectRemoved, static_cast<const void *>(e) });
    }

    void uDeathEvent(const void *) { hideAnimation(); }
    void uSelected(const void *) { selectEffect(); }
    void uUnselected(const void *) { removeSelectEffect(); }
    void uMoved(const void *);
    void uRotated(const void *);
    void uSkillStarted(const void *);
    void uSkillFinished(const void *);
    void uSkillAdvance(const void *);
    void uHealthChanged(const void *);
    void uEnergyConsumed(const void *);
    void uSpecialChanged(const void *);
    void uRageChanged(const void *);
    void uEffectAdded(const void *eff) { _add_effect_item(reinterpret_cast<const UnitEffect *>(eff)); }
    void uEffectRemoved(const void *eff);

    void showAnimation();
    void hideAnimation();

    void selectEffect();
    void removeSelectEffect();

private:

    template <typename... Args>
    void _add_animations(const Animation& a, Args&&... args) { _add_animations(a); _add_animations(args...); }

    void _add_animations(const Animation& a);

    void _update_effects();
    void _add_effect_item(const UnitEffect *);

    void _init();

    void _init_bar(ProgressBarItem *var, QColor color, UIntegerType width, UIntegerType height, UIntegerType value = 100);

    AnimatedObject *_obj;
    QGraphicsEffect *_select_effect;
    ProgressBarItem *_health_bar;
    ProgressBarItem *_energy_bar;
    ProgressBarItem *_special_bar;
    ProgressBarItem *_rage_bar;
    EventQueue _events;

    std::map<const UnitEffect *, PartialImageItem *> _effect_itens;

    static std::map<std::type_index, QImage> _effect_images;
};

} /* namespace unitanimation */

#endif // BASICUNITGRAPHICITEM_H
