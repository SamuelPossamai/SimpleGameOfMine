
#ifndef SKILLFACTORY_GENERICSKILLFACTORY_H
#define SKILLFACTORY_GENERICSKILLFACTORY_H

#include "unitskillfactory.h"

namespace skillfactory {

template<typename T>
class GenericSkillFactory : public UnitSkillFactory {

protected:

    virtual UnitSkill *createSkill(const VariantDataInfo& v) override { return T::create(v); }
};

} /* namespace skillfactory */

#endif // SKILLFACTORY_GENERICSKILLFACTORY_H
