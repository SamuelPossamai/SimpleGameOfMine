
#ifndef SIMPLEMEMORYMANAGER_H
#define SIMPLEMEMORYMANAGER_H

#include <map>

#include <memory/memorymanager.h>

template <typename T, typename Compare = std::less<T *> >
class SimpleMemoryManager : public MemoryManager {

    struct CopyInfo;
    using CopiesContainer = std::map<T *, CopyInfo, Compare>;

public:

    using CompareType = Compare;

    explicit SimpleMemoryManager(const CompareType& comp = CompareType(), bool add_man_list = true) :
        MemoryManager(add_man_list), _copies(comp) {}

    explicit SimpleMemoryManager(bool add_man_list) : SimpleMemoryManager(CompareType(), add_man_list) {}

    virtual ~SimpleMemoryManager() { for(auto copy : _copies) delete copy.first; }

    T *findCopy(const T * obj) { 
        
        auto it = getIterator(obj);
        
        if(it == _copies.end()) return nullptr;
        
        return it->first; 
    }
    
    const T *findCopy(const T * obj) const { return const_cast<SimpleMemoryManager *>(this)->findCopy(obj); }
    
    T *addCopy(T *obj, UIntegerType credits = 100, UIntegerType dependents = 0) {
        
        auto p = _copies.insert(std::make_pair(obj, CopyInfo{ credits, dependents }));
        
        return p.first->first;
    }
    
    T *incDependents(const T * obj) {
        
        auto it = getIterator(obj);

        if(it == _copies.end()) return nullptr;
        
        it->second.dependents++;

        return it->first;   
    }
    
    T *decDependents(const T * obj) {
           
        auto it = getIterator(obj);

        if(it == _copies.end()) return nullptr;

        UIntegerType& dependents = it->second.dependents;

        if(dependents) dependents--;
        else return nullptr;

        return it->first;
    }

    /*!
     * \brief Delete some copies of memory, to be deleted it must not have any dependence
     * \brief Objects that hasn't been accessed recently by get method have higher priority to be deleted
     * \param v Higher the value higher the number of deleted copies, if 0 none will be deleted
     */
    void clean(UIntegerType v);
    
    UIntegerType objects() const { return _copies.size(); }

protected:

    virtual void memoryManagerClean(UIntegerType v) override { clean(v); }

private:

    typename CopiesContainer::iterator getIterator(const T *obj);

    struct CopyInfo {

        UIntegerType useCredits;
        UIntegerType dependents;
    };

    CopiesContainer _copies;
};


template<typename T, typename Compare>
typename SimpleMemoryManager <T, Compare>::CopiesContainer::iterator
        SimpleMemoryManager <T, Compare>::getIterator(const T *obj) {

    auto it = _copies.find(const_cast<T *>(obj));

    if(it != _copies.end()) { it->second.useCredits = 100; }

    return it;
}

template<typename T, typename Compare>
void SimpleMemoryManager<T, Compare>::clean(UIntegerType v) {

    auto it = _copies.begin();
    while(it != _copies.end()) {

        if(it->second.dependents) {

            it++;
            continue;
        }

        auto& cur_v = it->second.useCredits;

        if(cur_v <= v) {

            auto *ptr = it->first;
            it = _copies.erase(it);
            delete ptr;
        }
        else {

            cur_v -= v;
            it++;
        }
    }
}

#endif // SIMPLEMEMORYMANAGER_H
