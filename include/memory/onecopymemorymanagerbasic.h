
#ifndef ONECOPYMEMORYMANAGERBASIC_H
#define ONECOPYMEMORYMANAGERBASIC_H

#include <map>

#include <memory/memorymanager.h>

/*!
 * \brief Class meant to be used to keep one copy only of an instance of T
 * \tparam T Type of the objects that are been manageds by OneCopyMemoryManagerBasic
 * \tparam Compare Type of the function/functor that is used to compare(less) the manageds objects, by default std::less<T>
 */
template <typename T, typename Compare = std::less<T> >
class OneCopyMemoryManagerBasic : public MemoryManager {

    class CompareFunctor;

    struct CopyInfo;
    using CopiesContainer = std::map<T *, CopyInfo, CompareFunctor>;

public:

    using CompareType = Compare;
    using CopyFunctionType = T *(*)(const T&);

    /*!
     * \brief Contruct an OneCopyMemoryManagerBasic, it must not be constructed before main
     * \param comp Compare function/functor, used internally to verify if the copy is already present
     * \param add_man_list If true, the object will be added to the memory managers list
     */
    explicit OneCopyMemoryManagerBasic(const CompareType& comp = CompareType(), bool add_man_list = true) :
        MemoryManager(add_man_list), _copies(CompareFunctor(comp)) {}

    /*!
     * \brief Contruct an OneCopyMemoryManagerBasic, it must not be constructed before main
     * \param add_man_list If true. the object will be added to the memory managers list
     */
    explicit OneCopyMemoryManagerBasic(bool add_man_list) : OneCopyMemoryManagerBasic(CompareType(), add_man_list) {}

    /*!
     * \brief Delete all copies, even if it has dependencies
     */
    ~OneCopyMemoryManagerBasic() { for(auto copy : _copies) delete std::get<0>(copy); }

    /*!
     * \brief Get the copy of an object that is managed by the memory manager
     * \param func Function to create an dynamically allocated with new object, if there isn't a copy of it yet
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return Return a pointer to a dynamically allocated object equal(It depends on the compare function) to 'obj'
     */
    T *get(CopyFunctionType func, const T& obj) { return getIterator(func, obj)->first; }

    /*!
     * \brief Get the copy of an object that is managed by the memory manager and increment the dependency counter
     * \brief The object will not be deleted by clean method if the dependency counter is not zero
     * \param func Function to create an dynamically allocated with new object, if there isn't a copy of it yet
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return Return a pointer to an dynamically allocated object equal(It depends on the compare function) to 'obj'
     */
    T *dependentGet(CopyFunctionType func, const T& obj) {

        auto it = getIterator(func, obj);

        it->second.dependents++;

        return it->first;
    }

    /*!
     * \brief Decrement the dependency counter
     * \brief The object will not be deleted by clean method if the dependency counter is not zero
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return true if it decrements successfully, false if there is no copy or the copy has no dependencies
     */
    bool noLongerDepend(const T& obj) {

        auto it = getIterator(nullptr, obj);

        if(it == _copies.end()) return false;

        UIntegerType& dependents = it->second.dependents;

        if(dependents) dependents--;
        else return false;

        return true;
    }

    /*!
     * \brief Delete some copies of memory, to be deleted it must not have any dependence
     * \brief Objects that hasn't been accessed recently by get method have higher priority to be deleted
     * \param v Value in [0, 100], higher the value higher the number of deleted copies, if 0 none will be deleted
     */
    void clean(UIntegerType v);

protected:

    typename CopiesContainer::iterator getIterator(CopyFunctionType func, const T& obj);
    virtual void memoryManagerClean(UIntegerType v) override { clean(v); }

private:

    class CompareFunctor {

    public:

        CompareFunctor(const Compare& comp) : _comp(comp) {}

        bool operator()(const typename CopiesContainer::key_type& obj1, const typename CopiesContainer::key_type& obj2) const {

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
typename OneCopyMemoryManagerBasic<T, Compare>::CopiesContainer::iterator
        OneCopyMemoryManagerBasic<T, Compare>::getIterator(CopyFunctionType func, const T& obj) {

    auto it = _copies.find(&const_cast<T&>(obj));

    if(it != _copies.end()) {

        it->second.useCredits = 100;
        return it;
    }

    if(func == nullptr) return _copies.end();

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
