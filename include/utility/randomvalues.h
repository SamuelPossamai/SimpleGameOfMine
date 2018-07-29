
#ifndef RANDOMVALUES_H
#define RANDOMVALUES_H

#include <vector>

#include <config/types.h>

#include "random.h"

namespace utility {

/*!
 * \brief Class meant to select a group of itens from certain parameters
 * \tparam T Type of the itens that are meant to be selected using this class
 */
template <typename T>
class RandomValues {

    struct RandomValueContent {

        T value;
        UIntegerType priority;
    };

public:

    using ValuesContainer = std::vector<T>;

    /*!
     * \brief Construct an object of this class passing the interval of values for the selected itens group size
     * \param min Minimum amount of itens that this object will select
     * \param max Maximum amount of itens that this object will select, max value included
     */
    RandomValues(UIntegerType min, UIntegerType max) : _min(min), _max(max) {}

    /*!
     * \brief Construct an object of this class passing the maximum size for the selected itens group size
     * \brief Same as RandomValue(0, max)
     * \param max Maximim amount of itens that this object will select, amx value included
     * \sa RandomValue(UIntegerType, UIntegerType)
     */
    explicit RandomValues(UIntegerType max = 1) : RandomValues(0, max) {}

    /*!
     * \brief Generate an random group of itens based on their priority and return it
     * \sa add(const T&, cosnt UIntegerType&), RandomValues(UIntegerType, UIntegerType)
     * \return A group of itens randonly selecteds
     */
    ValuesContainer getValues() const;

    /*!
     * \brief Add an item to the list of itens that can be selecteds
     * \param value Item value
     * \param priority Priority of the item, higher the priority higher the chances to be selected
     * \sa getValue()
     */
    void add(const T& value, const UIntegerType& priority) { _values.push_back({ value, priority }); }

    /*!
     * \brief Clear all the itens added to this object
     * \sa add(const T&, const UIntegerType&)
     */
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
