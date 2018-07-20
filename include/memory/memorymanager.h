
#ifndef MEMORY_MEMORYMANAGER_H
#define MEMORY_MEMORYMANAGER_H

#include <vector>

#include <config/types.h>

class MemoryManager {

public:

    explicit MemoryManager(bool add = true) { if(add) _managers.push_back(this); }
    virtual ~MemoryManager();

    void clean(UIntegerType v) { this->memoryManagerClean(v); }
    static void cleanAll(UIntegerType v) { for(MemoryManager *m : _managers) m->clean(v);  }

protected:

    virtual void memoryManagerClean(UIntegerType v) = 0;

private:

    static std::vector<MemoryManager *> _managers;
};

#endif // MEMORY_MEMORYMANAGER_H
