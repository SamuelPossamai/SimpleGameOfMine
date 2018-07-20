
#include <functional>

#include "memorymanager.h"

std::vector<MemoryManager *> MemoryManager::_managers;

MemoryManager::~MemoryManager() {

    auto it = std::find(_managers.begin(), _managers.end(), this);

    if(it != _managers.end()) {

        *it = _managers.back();
        _managers.pop_back();
    }
}

