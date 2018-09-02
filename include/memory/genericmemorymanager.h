
#ifndef GENERICMEMORYMANAGER_H
#define GENERICMEMORYMANAGER_H

#include "simplememorymanager.h"

class GenericMemoryManagerManagedObject;

struct GenericMemoryManagerCompareFunctor {
    
    bool operator()(const GenericMemoryManagerManagedObject * const &, const GenericMemoryManagerManagedObject * const &) const;
};

class GenericMemoryManager : public SimpleMemoryManager<GenericMemoryManagerManagedObject, GenericMemoryManagerCompareFunctor> {

    using Base = SimpleMemoryManager<GenericMemoryManagerManagedObject, GenericMemoryManagerCompareFunctor>;
    
public:

    using ManagedObject = GenericMemoryManagerManagedObject;
    
    GenericMemoryManager(bool add_man_list = true) : SimpleMemoryManager(add_man_list) {}
};

class GenericMemoryManagerManagedObject {

public:

    GenericMemoryManagerManagedObject();
    virtual ~GenericMemoryManagerManagedObject();

    GenericMemoryManagerManagedObject *getObjCopy() { return getObjCopy(*this); }
    static GenericMemoryManagerManagedObject *getObjCopy(const GenericMemoryManagerManagedObject&);
    
    static GenericMemoryManager *memManager() { if(!_manager) _manager = new GenericMemoryManager; return _manager; }
    
    virtual bool manObjLessCompare(const GenericMemoryManagerManagedObject *) const { return false; };
    virtual GenericMemoryManagerManagedObject *manObjClone() const = 0;
    
private:

    static GenericMemoryManager *_manager;
};

#endif // GENERICMEMORYMANAGER_H
