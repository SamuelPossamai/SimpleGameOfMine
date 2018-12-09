
#ifndef BASICPROJECTILEGRAPHICITEM_H
#define BASICPROJECTILEGRAPHICITEM_H

#include <cmath>

#include "engine/projectile.h"

#include "projectileanimationitem.h"
#include "animatedobject.h"

namespace projectileanimation {

class BasicProjectileGraphicItem : public ProjectileAnimationItem {

public:

    BasicProjectileGraphicItem(Projectile *p) : ProjectileAnimationItem(p), _obj(new AnimatedObject) {

        BasicProjectileGraphicItem::redraw();
    }

    virtual ~BasicProjectileGraphicItem() override { delete _obj; }

    virtual void redraw() override {

        if(projectile() == nullptr) return;

        if(projectile()->durability() == 0) {

            _obj->hide();
        }
        else {
            _obj->setPos(projectile()->x(), projectile()->y());
            _obj->setRotation(projectile()->angle()*180/M_PI);
            _obj->next();
        }
    }

    void setAnimations(const Animation& animation) {

        _obj->clearAnimations();
        _obj->addAnimation(animation);
    }

protected:


    virtual void addToScene(QGraphicsScene *scene) override { scene->addItem(_obj); }

    virtual void removeFromScene() override { scene()->removeItem(_obj); }

private:

    AnimatedObject *_obj;
};

} /* namespace projectileanimation */

#endif // BASICPROJECTILEGRAPHICITEM_H
