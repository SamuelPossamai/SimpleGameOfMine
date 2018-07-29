
#ifndef UTILITY_RANDOM_H
#define UTILITY_RANDOM_H

#include <random>

#include <config/types.h>

namespace utility {

/*!
 * \brief This class is meant to be an wrapper for obtaining random values with c++ 'random' library
 */
class Random {

public:

    /*!
     * \brief Method to get the minimal value the method 'get()' can generate
     * \sa max(), get()
     * \return The minimal value for 'get()' method
     */
    static UIntegerType min() { return _gen.min(); }

    /*!
     * \brief Method to get the maximum value the method 'get()' can generate
     * \sa min(), get()
     * \return The maximum value for 'get()' method
     */
    static UIntegerType max() { return _gen.max(); }

    /*!
     * \brief Discard 'z' values advancing the generator state
     * \param z Number of discarded values
     * \sa get()
     */
    static void discard(UIntegerType z) { _gen.discard(z); }

    /*!
     * \brief Return an value in [min(), max()]
     * \sa min(), max()
     * \return Pseudo-random number
     */
    static UIntegerType get() { return _gen(); }

    /*!
     * \brief Same as a call to get()
     * \sa get(), min(), max()
     * \return Pseudo-random number
     */
    UIntegerType operator()() { return get(); }

    /*!
     * \brief Return an pseudo-random integer in [min, max]
     * \param min Minimal value that this method will return
     * \param max Maximum value this method will return
     * \return Pseudo-random integer in [min, max]
     */
    static IntegerType uniformIntDistribution(IntegerType min, IntegerType max) {

        return std::uniform_int_distribution<IntegerType>(min, max)(_gen);
    }

    /*!
     * \brief Return an pseudo-random number in [min, max)
     * \param min Minimal value this method will return
     * \param max Maximum value this method will return
     * \return Pseudo-random number in [min, max)
     */
    static RealType realDistribution(RealType min, RealType max) { return std::uniform_real_distribution<RealType>(min, max)(_gen); }

private:

    static std::mt19937 _gen;
};

} /* namespace utility  */


#endif // UTILITY_RANDOM_H
