
#ifndef UTILITY_INTERVAL_H
#define UTILITY_INTERVAL_H

namespace utility {

/*!
 * \brief Class that represents a interval of values in [min, max]
 * \tparam T Type of the interval's values
 */
template<typename T>
class Interval {

public:

    /*!
     * \brief Construct an interval with only one value in it
     * \param value
     */
    Interval(T value) : _min(value), _max(value) {}

    /*!
     * \brief Construct an interval between two values [min, max]
     * \param min Minimal value in the interval
     * \param max Maximum value in the interval
     */
    Interval(T min, T max) : _min(min), _max(max) {}

    /*!
     * \brief Verify if a value is in the interval's range
     * \param value Value that will be verified
     * \sa min(), max()
     * \return Return true if value is in [min, max] otherwise return false
     */
    bool inRange(T value) const { return ((value >= _min) && (value <= _max)); }

    /*!
     * \brief Verify if the interval is valid
     * \return Return true if it is, false otherwise
     */
    bool isValid() const { return _min <= _max; }

    /*!
     * \brief Return the minimal value of the interval
     * \return Minimal value of the interval
     */
    T min() const { return _min; }

    /*!
     * \brief Return the maximum value of the interval
     * \return Maximum value of the interval
     */
    T max() const { return _max; }

private:

    T _min;
    T _max;
};

} /* namespace utility */

#endif // UTILITY_INTERVAL_H
