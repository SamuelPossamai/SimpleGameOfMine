
#ifndef UNITSKILLFACTORY_H
#define UNITSKILLFACTORY_H

#include "types.h"
#include "utility/variant.h"

class UnitSkillFactory {

public:

    using VariantDataInfo = utility::VariantDataInfo;

    virtual ~UnitSkillFactory() = default;

    UnitSkill *create(const VariantDataInfo& v = VariantDataInfo()) { return this->createSkill(v); }

protected:

    virtual UnitSkill *createSkill(const VariantDataInfo&) = 0;
};

#endif // UNITSKILLFACTORY_H
