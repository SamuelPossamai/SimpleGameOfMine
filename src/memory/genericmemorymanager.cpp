

#include <iostream>
#include <typeinfo>
#include <typeindex>

#include "genericmemorymanager.h"

GenericMemoryManager *GenericMemoryManager::ManagedObject::_manager = nullptr;

bool GenericMemoryManagerCompareFunctor::operator()(const GenericMemoryManagerManagedObject * const & mo1, const GenericMemoryManagerManagedObject * const & mo2) const {
    
    const std::type_info& id1 = typeid(*mo1);
    const std::type_info& id2 = typeid(*mo2);
    if(id1 != id2) {

        return std::type_index(id1) < std::type_index(id2);
    }

    return mo1->manObjLessCompare(mo2);
}

GenericMemoryManagerManagedObject::GenericMemoryManagerManagedObject() {

}

GenericMemoryManagerManagedObject::~GenericMemoryManagerManagedObject() {

    if(_manager) {
        
        if(_manager->objects() == 0) {
            
            delete _manager;
            
            _manager = nullptr;
        }
    }
}

GenericMemoryManagerManagedObject *GenericMemoryManagerManagedObject::getObjCopy(const GenericMemoryManagerManagedObject& obj) {
    
    auto *copy = memManager()->findCopy(&obj);
    
    if(copy == nullptr) return memManager()->addCopy(obj.manObjClone());
    
    return copy;
}
