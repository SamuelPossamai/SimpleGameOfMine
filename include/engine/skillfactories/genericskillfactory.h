
#ifndef SKILLFACTORY_GENERICSKILLFACTORY_H
#define SKILLFACTORY_GENERICSKILLFACTORY_H

#include "unitskillfactory.h"

namespace skillfactory {

template<typename T, bool = false>
class GenericSkillFactory : public UnitSkillFactory {

protected:

    virtual UnitSkill *createSkill(const VariantDataInfo& v) override { return T::create(v); }
};

template<typename T>
class GenericSkillFactory <T, true> : public UnitSkillFactory {

public:

    explicit GenericSkillFactory(const VariantDataInfo& v) : _v(v) {}

protected:

    virtual UnitSkill *createSkill(const VariantDataInfo& v) override {

        VariantDataInfo vdatainfo(v.begin(), v.end());

        vdatainfo.insert(v.begin(), v.end());

        return T::create(vdatainfo);
    }

private:

    VariantDataInfo _v;
};

} /* namespace skillfactory */

#endif // SKILLFACTORY_GENERICSKILLFACTORY_H
