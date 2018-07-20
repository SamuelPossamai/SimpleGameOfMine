
#ifndef ONECOPYMEMORYMANAGERBASIC_H
#define ONECOPYMEMORYMANAGERBASIC_H

#include <map>

#include <memory/memorymanager.h>

template <typename T, typename Compare = std::less<T> >
class OneCopyMemoryManagerBasic : public MemoryManager {

    class CompareFunctor;

    struct CopyInfo;
    using CopiesContainer = std::map<T *, CopyInfo, CompareFunctor>;

public:

    using CompareType = Compare;
    using CopyFunctionType = T *(*)(const T&);

    explicit OneCopyMemoryManagerBasic(const CompareType& comp = CompareType(), bool add_man_list = true) :
        MemoryManager(add_man_list), _copies(CompareFunctor(comp)) {}

    explicit OneCopyMemoryManagerBasic(bool add_man_list) : OneCopyMemoryManagerBasic(CompareType(), add_man_list) {}

    ~OneCopyMemoryManagerBasic() { for(auto copy : _copies) delete std::get<0>(copy); }

    T *get(CopyFunctionType func, const T& obj) { return getIterator(func, obj)->first; }

    T *dependentGet(CopyFunctionType func, const T& obj) {

        auto it = getIterator(func, obj);

        it->second.dependents++;

        return it->first;
    }

    void noLongerDepend(CopyFunctionType func, const T& obj) {

        auto it = getIterator(func, obj);

        UIntegerType& dependents = it->second.dependents;

        if(dependents) dependents--;
    }

    void clean(UIntegerType v);

protected:

    typename CopiesContainer::iterator getIterator(CopyFunctionType func, const T& obj);
    virtual void memoryManagerClean(UIntegerType v) override { clean(v); }

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
typename OneCopyMemoryManagerBasic<T, Compare>::CopiesContainer::iterator OneCopyMemoryManagerBasic<T, Compare>::getIterator(CopyFunctionType func, const T& obj) {

    auto it = _copies.find(&const_cast<T&>(obj));

    if(it != _copies.end()) {

        it->second.useCredits = 100;
        return it;
    }

    T *new_obj = func(obj);

    auto p = _copies.insert(std::make_pair(new_obj, CopyInfo{ 100, 0 }));

    return p.first;
}

template<typename T, typename Compare>
void OneCopyMemoryManagerBasic<T, Compare>::clean(UIntegerType v /* = 50 */) {

    auto it = _copies.begin();
    while(it != _copies.end()) {

        if(it->second.dependents) {

            it++;
            continue;
        }

        auto& cur_v = it->second.useCredits;

        if(cur_v <= v) {

            delete it->first;
            it = _copies.erase(it);
        }
        else {

            cur_v -= v;
            it++;
        }
    }
}

#endif // ONECOPYMEMORYMANAGERBASIC_H
