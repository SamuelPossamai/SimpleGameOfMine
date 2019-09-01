
#ifndef ITERATORWRAPPER_H
#define ITERATORWRAPPER_H

#include <iterator>

namespace utility {

template<typename ITER, typename ACCESS, bool CAN_ACCESS_BASE = true>
class IteratorWrapper {

public:

    using iterator_category = typename std::iterator_traits<ITER>::iterator_category;
    using value_type = typename std::remove_reference<decltype(ACCESS()(typename std::iterator_traits<ITER>::value_type()))>::type;
    using difference_type = typename std::iterator_traits<ITER>::difference_type;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    IteratorWrapper() = default;
    IteratorWrapper(const ITER& iter) : _iter(iter) {}
    IteratorWrapper(const IteratorWrapper&) = default;

    bool operator==(const IteratorWrapper& other) const { return _iter == other._iter; }
    bool operator!=(const IteratorWrapper& other) const { return _iter != other._iter; }
    bool operator>=(const IteratorWrapper& other) const { return _iter >= other._iter; }
    bool operator<=(const IteratorWrapper& other) const { return _iter <= other._iter; }
    bool operator>(const IteratorWrapper& other) const { return _iter > other._iter; }
    bool operator<(const IteratorWrapper& other) const { return _iter < other._iter; }

    IteratorWrapper& operator++() { ++_iter; return *this; }
    IteratorWrapper operator++(int) { return _iter++; }
    IteratorWrapper& operator--() { --_iter; return *this; }
    IteratorWrapper operator--(int) { return _iter--; }

    IteratorWrapper operator+(difference_type val) const { _iter + val; }
    IteratorWrapper operator-(difference_type val) const { _iter - val; }

    IteratorWrapper& operator+=(difference_type val) { return _iter += val; }
    IteratorWrapper operator-=(difference_type val) { return _iter -= val; }

    reference operator[](difference_type val) { return *IteratorWrapper(_iter[val]); }
    const_reference operator[](difference_type val) const { return (*const_cast<IteratorWrapper *>(this))[val]; }

    reference operator *() { return ACCESS()(*_iter); }
    const_reference operator *() const { return **const_cast<IteratorWrapper *>(this); }
    pointer operator->() { return &ACCESS()(*_iter); }
    const_pointer operator->() const { return *const_cast<IteratorWrapper *>(this); }

protected:

    using iterator_type = ITER;

    iterator_type base() const { return _iter; }

private:

    iterator_type _iter;
};

template<typename ITER, typename ACCESS>
class IteratorWrapper <ITER, ACCESS, true> : public IteratorWrapper<ITER, ACCESS, false> {

    using Base = IteratorWrapper<ITER, ACCESS, false>;

public:

    using Base::iterator_type;

    using Base::Base;
    using Base::base;
};


} /* namespace utility */

#endif // ITERATORWRAPPER_H
