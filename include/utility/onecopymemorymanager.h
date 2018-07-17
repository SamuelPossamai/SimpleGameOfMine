
#ifndef UTILITY_ONECOPYMEMORYMANAGER_H
#define UTILITY_ONECOPYMEMORYMANAGER_H

#include <map>

#include <config/types.h>

namespace utility {

template <typename T, typename Compare = std::less<T> >
class OneCopyMemoryManager {

    class CompareFunctor;

    struct CopyInfo;
    using CopiesContainer = std::map<T *, CopyInfo, CompareFunctor>;

public:

    OneCopyMemoryManager(const Compare& comp = Compare()) : _copies(CompareFunctor(comp)) {}
    ~OneCopyMemoryManager() { for(auto copy : _copies) delete std::get<0>(copy); }

    template<typename... Args>
    T *get(Args... args) { return getIterator(args...)->first; }

    template<typename... Args>
    T *dependentGet(Args... args) {

        auto it = getIterator(args...);

        it->second.dependents++;

        return it->first;
    }

    template<typename... Args>
    void noLongerDepend(Args... args) {

        auto it = getIterator(args...);

        UIntegerType& dependents = it->second.dependents;

        if(dependents) dependents--;
    }

    void clean(UIntegerType v = 50);
    void cleanSome() { clean(20); }
    void veryclean() { clean(100); }

protected:

    template<typename... Args>
    typename CopiesContainer::iterator getIterator(Args... args);

private:

    class CompareFunctor {

    public:

        CompareFunctor(const Compare& comp) : _comp(comp) {}

        bool operator()(const typename CopiesContainer::key_type& obj1, const typename CopiesContainer::key_type& obj2) {

            return _comp(*obj1, *obj2);
        }

    private:

        Compare _comp;
    };

    struct CopyInfo {

        UIntegerType useCredits;
        UIntegerType dependents;
    };

    CopiesContainer _copies;
};

template<typename T, typename Compare>
template<typename... Args>
typename OneCopyMemoryManager<T, Compare>::CopiesContainer::iterator OneCopyMemoryManager<T, Compare>::getIterator(Args... args) {

    T obj(args...);

    auto it = _copies.find(&obj);

    if(it != _copies.end()) {

        it->second.useCredits = 100;
        return it;
    }

    T *new_obj = new T(args...);

    auto p = _copies.insert(std::make_pair(new_obj, CopyInfo{ 100, 0 }));

    return p.first;
}

template<typename T, typename Compare>
void OneCopyMemoryManager<T, Compare>::clean(UIntegerType v /* = 50 */) {

    auto it = _copies.begin();
    while(it != _copies.end()) {

        if(it->second.dependents) continue;

        auto& cur_v = it->second.useCredits;

        if(cur_v <= v) it = _copies.erase(it);
        else {

            cur_v -= v;
            it++;
        }
    }
}

} /* namespace utility */

#endif // UTILITY_ONECOPYMEMORYMANAGER_H
