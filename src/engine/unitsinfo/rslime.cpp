
#include <engine/unit.h>

#include "unitsinfo/rslime.h"
#include "effects/regeneration.h"

using namespace unitsinfo;

RSlime *RSlime::_info = nullptr;

void RSlime::init(Unit *u) const {

    u->addEffect(effect::Regeneration::getEffect(1, 50));
}

RSlime *RSlime::getInfo() {

    if(_info) return _info;

    auto *slime_info = Slime::getInfo();

    _info = new RSlime;

    _info->copy(static_cast<UnitInfo *>(slime_info));
    _info->setSpeed(_info->speed()*0.9);

    return _info;
}

