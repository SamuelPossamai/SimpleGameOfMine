
#ifndef BASICUNITGRAPHICITEM_H
#define BASICUNITGRAPHICITEM_H

#include <queue>

#include "animation/unitanimationitem.h"
#include "animatedobject.h"
#include "progressbaritem.h"

namespace unitanimation {

class BasicUnitGraphicItem : public UnitAnimationItem {

    using EventQueue = std::queue<void (BasicUnitGraphicItem::*)()>;

public:

    BasicUnitGraphicItem(Unit *u);

    virtual ~BasicUnitGraphicItem() { delete _obj; delete _health_bar; }

    virtual void redraw() override {

        while(!_events.empty()) {

            (this->*(_events.front()))();
            _events.pop();
        }
    }

    template <typename... Animations>
    void setAnimations(const Animation& idle, Animations&&... skill_animations) {

        _obj->clearAnimations();
        _add_animations(idle, skill_animations...);
    }

protected:

    virtual void addToScene(QGraphicsScene *scene) override {

        scene->addItem(_health_bar);
        scene->addItem(_obj);
        if(_energy_bar) scene->addItem(_energy_bar);
    }

    virtual void removeFromScene() override {

        scene()->removeItem(_health_bar);
        scene()->removeItem(_obj);
        if(_energy_bar) scene()->removeItem(_energy_bar);
    }

    virtual void unitDeathEvent(Unit *) override { _events.push(&BasicUnitGraphicItem::unitDeathEvent); }
    virtual void unitSelected(Unit *) override { _events.push(&BasicUnitGraphicItem::unitSelected); }
    virtual void unitUnselected(Unit *) override { _events.push(&BasicUnitGraphicItem::unitUnselected); }
    virtual void unitMoved(Unit *) override { _events.push(&BasicUnitGraphicItem::unitMoved); }
    virtual void unitRotated(Unit *) override { _events.push(&BasicUnitGraphicItem::unitRotated); }
    virtual void unitSkillStarted(Unit *) override { _events.push(&BasicUnitGraphicItem::unitSkillStarted); }
    virtual void unitSkillFinished(Unit *) override { _events.push(&BasicUnitGraphicItem::unitSkillFinished); }
    virtual void unitSkillAdvance(Unit *) override { _events.push(&BasicUnitGraphicItem::unitSkillAdvance); }
    virtual void unitReceivedDamage(Unit *) override { _events.push(&BasicUnitGraphicItem::unitHealthChanged); }
    virtual void unitHealed(Unit *) override { _events.push(&BasicUnitGraphicItem::unitHealthChanged); }
    virtual void unitEnergyConsumed(Unit *) override { if(_energy_bar) _events.push(&BasicUnitGraphicItem::unitEnergyConsumed); }

    void unitDeathEvent() { hideAnimation(); }
    void unitSelected() { selectEffect(); }
    void unitUnselected() { removeSelectEffect(); }
    void unitMoved();
    void unitRotated();
    void unitSkillStarted();
    void unitSkillFinished();
    void unitSkillAdvance();
    void unitHealthChanged();
    void unitEnergyConsumed();

    void showAnimation() { _obj->show(); _health_bar->show(); if(_energy_bar) _energy_bar->show(); }
    void hideAnimation() { _obj->hide(); _health_bar->hide(); if(_energy_bar) _energy_bar->hide(); }

    void selectEffect();
    void removeSelectEffect();

private:

    template <typename... Args>
    void _add_animations(const Animation& a, Args&&... args) { _add_animations(a); _add_animations(args...); }

    void _add_animations(const Animation& a);

    AnimatedObject *_obj;
    QGraphicsEffect *_select_effect;
    ProgressBarItem *_health_bar;
    ProgressBarItem *_energy_bar;
    EventQueue _events;
};

} /* namespace unitanimation */

#endif // BASICUNITGRAPHICITEM_H
