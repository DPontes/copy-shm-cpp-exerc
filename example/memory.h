#ifndef MEMORY_H_
#define MEMORY_H_

#include "shared_data.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

using namespace boost::interprocess;

class Memory {
  public:
    ~Memory();
    void mapRegion();
    void* getRegionAddress();

  protected:
    shared_memory_object shm;
    mapped_region region;
};

class createdMemory : public Memory {
  public:
    createdMemory() { shared_memory_object::remove("MySharedMemory"); }
    ~createdMemory() { shared_memory_object::remove("MySharedMemory"); }

    void createMemObj();
    void setSize();
};

class openedMemory : public Memory {
  public:
    openedMemory() {}
    ~openedMemory() { shared_memory_object::remove("MySharedMemory"); }

    void openMemObj();
};

#endif /* MEMORY_H_ */
