
#ifndef RANDOMVALUES_H
#define RANDOMVALUES_H

#include <vector>

#include <config/types.h>

#include "random.h"

namespace utility {

template <typename T>
class RandomValues {

    struct RandomValueContent {

        T value;
        UIntegerType priority;
    };

public:

    using ValuesContainer = std::vector<T>;

    RandomValues(UIntegerType min, UIntegerType max) : _min(min), _max(max) {}
    explicit RandomValues(UIntegerType max = 1) : RandomValues(0, max) {}

    ValuesContainer getValues() const;

    void add(const T& value, const UIntegerType& priority) { _values.push_back({ value, priority }); }

    void clear() { _values.clear(); }

private:

    void _get_one(ValuesContainer& c, UIntegerType value) const {

        auto before_end = _values.end() - 1;
        auto it = _values.begin();
        for(; it != before_end; it++) {

            if(value < it->priority) break;

            value -= it->priority;
        }

        c.push_back(it->value);
    }

    UIntegerType _min, _max;
    std::vector<RandomValueContent> _values;
};

template<typename T>
typename RandomValues<T>::ValuesContainer RandomValues<T>::getValues() const {

    UIntegerType priority_sum = 0;

    for(auto it = _values.begin(); it != _values.end(); it++) priority_sum += it->priority;

    if(priority_sum == 0) return ValuesContainer();

    UIntegerType q = Random::uniformIntDistribution(_min, _max);

    ValuesContainer c;
    for(UIntegerType i = 0; i < q; i++) _get_one(c, Random::uniformIntDistribution(0, priority_sum - 1));

    return c;
}

} /* namespace utility */

#endif // RANDOMVALUES_H
