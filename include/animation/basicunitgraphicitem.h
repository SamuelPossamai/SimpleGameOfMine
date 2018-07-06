
#ifndef BASICUNITGRAPHICITEM_H
#define BASICUNITGRAPHICITEM_H

#include <queue>

#include "animation/unitanimationitem.h"

class BasicUnitGraphicItem : UnitAnimationItem {

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

protected:

    virtual void addToScene(QGraphicsScene *scene) override { scene->addItem(_health_bar); scene->addItem(_obj); }
    virtual void removeFromScene() override { scene()->removeItem(_health_bar); scene()->removeItem(_obj); }

    virtual void unitDeathEvent(Unit *) override { _events.push(&BasicUnitGraphicItem::unitDeathEvent); }
    virtual void unitSelected(Unit *) override { _events.push(&BasicUnitGraphicItem::unitSelected); }
    virtual void unitUnselected(Unit *) override { _events.push(&BasicUnitGraphicItem::unitUnselected); }
    virtual void unitMoved(Unit *) override { _events.push(&BasicUnitGraphicItem::unitMoved); }

    void unitDeathEvent() { hideAnimation(); }
    void unitSelected() { selectEffect(); }
    void unitUnselected() { removeSelectEffect(); }
    void unitMoved();

    void showAnimation() { _obj->show(); _health_bar->show(); }
    void hideAnimation() { _obj->hide(); _health_bar->hide(); }

    void selectEffect() { _select_effect->setEnabled(true); }
    void removeSelectEffect() { _select_effect->setEnabled(false); }

private:

    AnimatedObject *_obj;
    QGraphicsEffect *_select_effect;
    ProgressBarItem *_health_bar;
    EventQueue _events;
};

#endif // BASICUNITGRAPHICITEM_H
