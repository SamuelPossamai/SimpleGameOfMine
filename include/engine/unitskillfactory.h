
#ifndef UNITSKILLFACTORY_H
#define UNITSKILLFACTORY_H

#include <variant.h>

#include "types.h"

class UnitSkillFactory {

public:

    using VariantDataInfo = sutils::VariantDataInfo;

    virtual ~UnitSkillFactory() = default;

    UnitSkill *create(const VariantDataInfo& v = VariantDataInfo()) { return this->createSkill(v); }

protected:

    virtual UnitSkill *createSkill(const VariantDataInfo&) = 0;
};

#endif // UNITSKILLFACTORY_H
