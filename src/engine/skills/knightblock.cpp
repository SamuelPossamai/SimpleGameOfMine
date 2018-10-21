
#include "effects/shield.h"
#include "unitsinfo/unitclassinfo.h"
#include "unit.h"
#include "skills/knightblock.h"

using namespace skill;

KnightBlock *KnightBlock::_skill = nullptr;

UIntegerType KnightBlock::action(Unit *u, EngineMap *, ProjectileCreationInterface&, const Info& info) {

    if(info.step > 0) return 0;

    u->setAngle(info.angle);

    static const UIntegerType dur = 30;

    auto u_info = static_cast<const unitsinfo::UnitClassInfo *>(u->unitInfo());

    UnitEffect *effect = effect::Shield::getEffect(
                20 + (u_info->attributes().strength() + u_info->attributes().vitality())/4);

    u->removeEffect(effect);
    u->addEffect(effect, dur);

    return 0.9*dur;
}
