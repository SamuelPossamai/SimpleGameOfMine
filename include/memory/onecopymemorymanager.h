
#ifndef MEMORY_ONECOPYMEMORYMANAGER_H
#define MEMORY_ONECOPYMEMORYMANAGER_H

#include <memory/onecopymemorymanagerbasic.h>

template <typename T, typename Compare = std::less<T> >
class OneCopyMemoryManager {

    using Basic = OneCopyMemoryManagerBasic<T, Compare>;

public:

    using CompareType = typename Basic::CompareType;
    using CopyFunctionType = typename Basic::CopyFunctionType;

    explicit OneCopyMemoryManager(const CopyFunctionType& copy = _copy,
                                  const CompareType& comp = CompareType(),
                                  bool add_man_list = true) :
        _add_to_managers_group(add_man_list), _compare_function(comp), _copy_function(copy), _basic(nullptr) {}

    explicit OneCopyMemoryManager(bool add_man_list) : OneCopyMemoryManager(_copy, CompareType(), add_man_list) {}

    template<typename... Args>
    T *emplaceGet(Args... args) { return get(T(args...)); }

    T *get(const T& obj) {

        _basic_constructed_verify();
        return _basic->get(_copy_function, obj);
    }

    template<typename... Args>
    T *dependentEmplaceGet(Args... args) { return dependentGet(T(args...)); }

    T *dependentGet(const T& obj) {

        _basic_constructed_verify();
        return _basic->dependentGet(_copy_function, obj);
    }

    void noLongerDepend(const T& obj) {

        _basic_constructed_verify();
        _basic->noLongerDepend(_copy_function, obj);
    }

    void clean(UIntegerType v = 50) {

        _basic_constructed_verify();
        _basic->clean(v);
    }

    void cleanSome() { clean(20); }
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
