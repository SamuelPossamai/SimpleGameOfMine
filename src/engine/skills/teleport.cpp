
#include <cmath>

#include <utility/random.h>
#include <engine/map.h>
#include <engine/unit.h>

#include "skills/teleport.h"

using namespace skill;
using namespace utility;

Teleport *Teleport::_skill;

UIntegerType Teleport::action(Unit *u, Map *, const Info& info) {

    if(info.step == 0) {

        if(u->consumeEnergy(1)) return 10;
        else return 0;
    }
    if(info.step > 10) return 0;

    teleportUnit(u);

    return 10;
}

bool Teleport::teleportUnit(Unit *u) {


    Map::PointType p_max = u->maxPosition();

    u->setAngle(Random::realDistribution(0, 2*M_PI));

    for(UIntegerType i = 0; i < 10; i++) {

        Map::PointType new_p;
        new_p.x = Random::realDistribution(u->size(), p_max.x);
        new_p.y = Random::realDistribution(u->size(), p_max.y);

        if(u->setPos(new_p)) return true;
    }

    return false;
}
