
#ifndef UTILITY_RANDOM_H
#define UTILITY_RANDOM_H

#include <random>

#include <config/types.h>

namespace utility {

class Random {

public:

    static UIntegerType min() { return _gen.min(); }
    static UIntegerType max() { return _gen.max(); }

    static void discard(UIntegerType z) { _gen.discard(z); }

    static UIntegerType get() { return _gen(); }

    UIntegerType operator()() { return get(); }

    static UIntegerType uniformIntDistribution(UIntegerType min, UIntegerType max) {

        return std::uniform_int_distribution<UIntegerType>(min, max)(_gen);
    }

private:

    static std::mt19937 _gen;
};

} /* namespace utility  */


#endif // UTILITY_RANDOM_H
