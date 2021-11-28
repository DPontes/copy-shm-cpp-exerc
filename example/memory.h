#ifndef MEMORY_H_
#define MEMORY_H_

#include "shared_data.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

class Memory {
  public:
    virtual ~Memory() = default;
    virtual void mapRegion() = 0;
    virtual void* getRegionAddress() = 0;
};

class createdMemory : public Memory {
  public:
    createdMemory() { shared_memory_object::remove("MySharedMemory"); }
    ~createdMemory() { shared_memory_object::remove("MySharedMemory"); }

    void createMemObj();
    void setSize();
    void mapRegion() override;
    void* getRegionAddress() override;

  private:
    shared_memory_object shm;
    mapped_region region;
};

class openedMemory : public Memory {
  public:
    openedMemory() {}
    ~openedMemory() { shared_memory_object::remove("MySharedMemory"); }

    void openMemObj();
    void mapRegion() override;
    void* getRegionAddress() override;
};

#endif /* MEMORY_H_ */
