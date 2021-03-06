
#include <cmath>

#include "enginemap.h"
#include "projectile.h"

bool Projectile::act() {

    if(_durability == 0) return false;

    if(_to_next_action == 0) _to_next_action = this->stepAction();
    else _to_next_action--;

    static const UIntegerType distance = 10;

    PositionType dx = distance*std::cos(_dir);
    PositionType dy = distance*std::sin(_dir);

    PointType new_pos(x() + dx, y() + dy);

    if(!map()->engineObjectMoveVerify(this, new_pos)) {

        this->collideAction(map(), nullptr);

        return _durability != 0;
    }

    auto v = map()->objectsInRange(pos(), size());

    for(auto obj : v) if(obj != this) {

        this->collideAction(map(), obj);
        if(_durability == 0) return false;
    }

    EngineObjectBase::setPos(new_pos);

    return true;
}
