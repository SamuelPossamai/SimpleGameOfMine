
#ifndef MEMORY_MEMORYMANAGER_H
#define MEMORY_MEMORYMANAGER_H

#include <vector>

#include <config/types.h>

/*!
 * \brief Abstract class to memory management, it has a list with memory managers that have been created
 * \brief Classes that are meant to manage memory should inherit it or have a member that inherits
 */
class MemoryManager {

public:

    /*!
     * \brief Construct an MemoryManagar and add it to the memory managers list, if add is true
     * \brief Objects added to the list must not be constructed before main(global or static variables)
     * \param add If true the object created will be added to the memory managers list
     */
    explicit MemoryManager(bool add = true) { if(add) _managers.push_back(this); }

    /*!
     * \brief Remove it from the memory managers list, if added
     */
    virtual ~MemoryManager();

    /*!
     * \brief Call memoryManagerClean for this memory manager
     * \brief it's meant to clean some not used memory
     * \param v This parameter should be between 0 and 100,<!--
     *      -->where 100 would delete all memory that can be deleted and 0 would delete none
     * \sa cleanAll(UIntegerType), memoryManagerClean(UIntegerType)
     */
    void clean(UIntegerType v) { this->memoryManagerClean(v); }

    /*!
     * \brief Call clean(v) for all the memory managers in the list
     * \brief it's meant to clean some memory from each memory manager
     * \param v This parameter should be in [0, 100], higher the value more memory should be cleaned
     * \sa clean(UIntegerType)
     */
    static void cleanAll(UIntegerType v) { for(MemoryManager *m : _managers) m->clean(v);  }

protected:

    /*!
     * \brief This method should be implemented to clean not used memory
     * \param v This parameter should be between 0 and 100,<!--
     *      -->where 100 would delete all memory that can be deleted and 0 would delete none
     * \sa cleanAll(UIntegerType), clean(UIntegerType)
     */
    virtual void memoryManagerClean(UIntegerType v) = 0;

private:

    static std::vector<MemoryManager *> _managers;
};

#endif // MEMORY_MEMORYMANAGER_H
