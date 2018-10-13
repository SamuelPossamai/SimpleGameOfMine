
#include "unit.h"
#include "projectiles/basicprojectile.h"

using namespace projectile;

void BasicProjectile::collideAction(Map *, EngineObject *obj) {

    if(obj == nullptr) {

        this->decreaseDurability(this->durability());
        return;
    }

    Unit *u = dynamic_cast<Unit *>(obj);

    if(u) {

        u->receiveDamage(_damage);
        this->decreaseDurability(this->durability());
        return;
    }

    Projectile *p = dynamic_cast<Projectile *>(obj);

    if(p) {

        UIntegerType dec = this->durability() > p->durability() ? this->durability() : p->durability();

        p->decreaseDurability(dec);
        this->decreaseDurability(dec);

        return;
    }
}
