
#ifndef UTILITY_INTERVAL_H
#define UTILITY_INTERVAL_H

namespace utility {

template<typename T>
class Interval {

public:

    Interval(T value) : _min(value), _max(value) {}
    Interval(T min, T max) : _min(min), _max(max) {}

    bool inRange(T value) const { return ((value >= _min) && (value <= _max)); }

    bool isValid() const { return _min <= _max; }

    T min() const { return _min; }
    T max() const { return _max; }

private:

    T _min;
    T _max;
};

} /* namespace utility */

#endif // UTILITY_INTERVAL_H
