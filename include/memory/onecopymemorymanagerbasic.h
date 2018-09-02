
#ifndef ONECOPYMEMORYMANAGERBASIC_H
#define ONECOPYMEMORYMANAGERBASIC_H

#include <map>

#include <memory/simplememorymanager.h>

template <typename T, typename Compare>
class OneCopyMemoryManagerBasicCompareFunctor {

    public:

        OneCopyMemoryManagerBasicCompareFunctor(const Compare& comp) : _comp(comp) {}

        bool operator()(const T * const obj1, const T * const obj2) const {

            return _comp(*obj1, *obj2);
        }

    private:

        Compare _comp;
};

/*!
 * \brief Class meant to be used to keep one copy only of an instance of T
 * \tparam T Type of the objects that are been manageds by OneCopyMemoryManagerBasic
 * \tparam Compare Type of the function/functor that is used to compare(less) the manageds objects, by default std::less<T>
 */
template <typename T, typename Compare = std::less<T> >
class OneCopyMemoryManagerBasic : public SimpleMemoryManager<T, OneCopyMemoryManagerBasicCompareFunctor<T, Compare> > {

    using CompareFunctor = OneCopyMemoryManagerBasicCompareFunctor<T, Compare>;
    using Base = SimpleMemoryManager<T, OneCopyMemoryManagerBasicCompareFunctor<T, Compare> >;
    
public:

    using CompareType = Compare;
    using CopyFunctionType = T *(*)(const T&);

    /*!
     * \brief Contruct an OneCopyMemoryManagerBasic, it must not be constructed before main
     * \param comp Compare function/functor, used internally to verify if the copy is already present
     * \param add_man_list If true, the object will be added to the memory managers list
     */
    explicit OneCopyMemoryManagerBasic(const CompareType& comp = CompareType(), bool add_man_list = true) :
        Base(CompareFunctor(comp), add_man_list) {}

    /*!
     * \brief Contruct an OneCopyMemoryManagerBasic, it must not be constructed before main
     * \param add_man_list If true. the object will be added to the memory managers list
     */
    explicit OneCopyMemoryManagerBasic(bool add_man_list) : OneCopyMemoryManagerBasic(CompareType(), add_man_list) {}

    /*!
     * \brief Delete all copies, even if it has dependencies
     */
    virtual ~OneCopyMemoryManagerBasic() {}

    /*!
     * \brief Get the copy of an object that is managed by the memory manager
     * \param func Function to create an dynamically allocated with new object, if there isn't a copy of it yet
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return Return a pointer to a dynamically allocated object equal(It depends on the compare function) to 'obj'
     */
    T *get(CopyFunctionType func, const T& obj) { 
        
        T *p = Base::findCopy(&obj);
        
        if(p == nullptr) return Base::addCopy(func(obj));
        
        return p;
    }

    /*!
     * \brief Get the copy of an object that is managed by the memory manager and increment the dependency counter
     * \brief The object will not be deleted by clean method if the dependency counter is not zero
     * \param func Function to create an dynamically allocated with new object, if there isn't a copy of it yet
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return Return a pointer to an dynamically allocated object equal(It depends on the compare function) to 'obj'
     */
    T *dependentGet(CopyFunctionType func, const T& obj) {

        T *p = Base::incDependents(&obj);
        
        if(p == nullptr) return Base::addCopy(func(obj), 100, 1);

        return p;
    }

    /*!
     * \brief Decrement the dependency counter
     * \brief The object will not be deleted by clean method if the dependency counter is not zero
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return true if it decrements successfully, false if there is no copy or the copy has no dependencies
     */
    bool noLongerDepend(const T& obj) {

        T *p = Base::decDependents(&obj);

        return p != nullptr;
    }
};

#endif // ONECOPYMEMORYMANAGERBASIC_H
