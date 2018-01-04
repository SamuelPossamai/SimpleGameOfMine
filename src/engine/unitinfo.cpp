
#include "unitinfo.h"

UIntegerType UnitInfo::callSkill(UIntegerType n, Unit *u, Map *m, UIntegerType step) const {

    return const_cast<UnitSkill *>(std::get<0>(_skills[n]))->action(u, m, step);
}
