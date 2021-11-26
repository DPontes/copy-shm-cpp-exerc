#include "shared_data.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstdio>
#include <iostream>
#include <thread>

using namespace boost::interprocess;

class Memory {
  public:
    Memory()    {
                    shared_memory_object::remove("MySharedMemory");
                }
    ~Memory()   {
                    shared_memory_object::remove("MySharedMemory");
                }

    void createMemObj() { shm = shared_memory_object(create_only, "MySharedMemory", read_write); }
    void setSize() { shm.truncate(sizeof(Image)); }
    void mapRegion() { region = mapped_region(shm, read_write); }
    void* getRegionAddress() { return region.get_address(); }

  private:
    shared_memory_object shm;
    mapped_region region;
};

int main()
{
    Memory mem;

    mem.createMemObj();
    mem.setSize();
    mem.mapRegion();
    void* addr = mem.getRegionAddress();

    // Construct the shared structure in memory
    Image* image = new (addr) Image;

    // Write some pixels
    {
        scoped_lock<interprocess_mutex> lock(image->mutex);
        image->data.fill(10);
    }

    // Wait until the other process ends
    while (1)
    {
        scoped_lock<interprocess_mutex> lock(image->mutex);
        if (std::all_of(image->data.begin(),
                        image->data.end(),
                        [](auto pixel) { return pixel == 11; }))
        {
            break;
        }
        else
        {
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
    }
    return 0;
}
