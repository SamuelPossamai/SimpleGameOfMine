
#ifndef MEMORY_ONECOPYMEMORYMANAGER_H
#define MEMORY_ONECOPYMEMORYMANAGER_H

#include <memory/onecopymemorymanagerbasic.h>

/*!
 * \brief Class meant to be used to keep one copy only of an instance of T
 * \brief Wrapper class, it is intended to use instead of OneCopyMemoryManagerBasic, if you want to construct it before main
 * \tparam T Type of the objects that are been manageds by OneCopyMemoryManager
 * \tparam Compare Type of the function/functor that is used to compare(less) the manageds objects, by default std::less<T>
 * \sa OneCopyMemoryManagerBasic
 */
template <typename T, typename Compare = std::less<T> >
class OneCopyMemoryManager {

    using Basic = OneCopyMemoryManagerBasic<T, Compare>;

public:

    using CompareType = typename Basic::CompareType;
    using CopyFunctionType = typename Basic::CopyFunctionType;

    /*!
     * \brief Construct an OneCopyMemoryManager
     * \param copy Function to create an dynamically allocated with new object, if there isn't a copy of it yet
     * \param comp Compare function/functor, used internally to verify if the copy is already present
     * \param add_man_list If true, the object will be added to the memory managers list
     */
    explicit OneCopyMemoryManager(const CopyFunctionType& copy = _copy,
                                  const CompareType& comp = CompareType(),
                                  bool add_man_list = true) :
        _add_to_managers_group(add_man_list), _compare_function(comp), _copy_function(copy), _basic(nullptr) {}

    /*!
     * \brief OneCopyMemoryManager Construt an OneCopyMemoryManager
     * \param add_man_list If true, the object will be added to the memory managers list
     */
    explicit OneCopyMemoryManager(bool add_man_list) : OneCopyMemoryManager(_copy, CompareType(), add_man_list) {}

    ~OneCopyMemoryManager() { if(_basic) delete _basic; }
    
    /*!
     * \brief Get the copy of an object that is managed by the memory manager
     * \param args Arguments to create an object that will be searched in the memory manager
     * \return Return a pointer to a dynamically allocated object equal(It depends on the compare function)<!--
     *      --> to the object created using 'args' as paremeters
     */
    template<typename... Args>
    T *emplaceGet(Args... args) { return get(T(args...)); }

    /*!
     * \brief Get the copy of an object that is managed by the memory manager
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return Return a pointer to a dynamically allocated object equal(It depends on the compare function) to 'obj'
     */
    T *get(const T& obj) {

        _basic_constructed_verify();
        return _basic->get(_copy_function, obj);
    }

    /*!
     * \brief Get the copy of an object that is managed by the memory manager and increment the dependency counter
     * \brief The object will not be deleted by clean method if the dependency counter is not zero
     * \param args Arguments to create an object that will be searched in the memory manager
     * \return Return a pointer to a dynamically allocated object equal(It depends on the compare function)<!--
     *      --> to the object created using 'args' as paremeters
     */
    template<typename... Args>
    T *dependentEmplaceGet(Args... args) { return dependentGet(T(args...)); }

    /*!
     * \brief Get the copy of an object that is managed by the memory manager and increment the dependency counter
     * \brief The object will not be deleted by clean method if the dependency counter is not zero
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return Return a pointer to an dynamically allocated object equal(It depends on the compare function) to 'obj'
     */
    T *dependentGet(const T& obj) {

        _basic_constructed_verify();
        return _basic->dependentGet(_copy_function, obj);
    }

    /*!
     * \brief Decrement the dependency counter
     * \brief The object will not be deleted by clean method if the dependency counter is not zero
     * \param obj Object that is been searched in the memory manager(It should be from a local scope)
     * \return true if it decrements successfully, false if there is no copy or the copy has no dependencies
     */
    void noLongerDepend(const T& obj) {

        _basic_constructed_verify();
        _basic->noLongerDepend(obj);
    }

    /*!
     * \brief Delete some copies of memory, to be deleted it must not have any dependence
     * \brief Objects that hasn't been accessed recently by get method have higher priority to be deleted
     * \param v Value in [0, 100], higher the value higher the number of deleted copies, if 0 none will be deleted
     */
    void clean(UIntegerType v = 50) {

        _basic_constructed_verify();
        _basic->clean(v);
    }

    /*!
     * \brief Same as a call to clean(20)
     * \sa clean(UIntegerType)
     */
    void cleanSome() { clean(20); }

    /*!
     * \brief Same as a call to clean(100)
     * \sa clean(UIntegerType)
     */
    void veryClean() { clean(100); }

private:

    void _basic_constructed_verify() { if(!_basic) _basic = new Basic(_compare_function, _add_to_managers_group); }
    static T *_copy(const T& obj) { return new T(obj); }

    bool _add_to_managers_group;
    CompareType _compare_function;
    CopyFunctionType _copy_function;

    Basic *_basic;
};

#endif // MEMORY_ONECOPYMEMORYMANAGER_H
