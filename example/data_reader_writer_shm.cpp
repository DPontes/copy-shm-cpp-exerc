#include "shared_data.h"
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstdio>
#include <iostream>

using namespace boost::interprocess;

class Memory {
  public:
    Memory()  {}
    ~Memory() { shared_memory_object::remove("MySharedMemory"); }

    void openMemObj() { shm = shared_memory_object(open_only, "MySharedMemory", read_write); }
    void mapRegion() { region = mapped_region(shm, read_write); }
    void* getRegionAddress() const { return region.get_address(); }

  private:
    shared_memory_object shm;
    mapped_region region;

};

int main()
{
    Memory mem;

    mem.openMemObj();
    mem.mapRegion();

    void* addr = mem.getRegionAddress();

    // Construct the shared structure in memory
    auto image = static_cast<Image*>(addr);

    scoped_lock<interprocess_mutex> lock(image->mutex);
    for (std::size_t i = 0; i < Image::size; ++i)
    {
        const auto current_pixel = image->data.at(i);
        image->data.at(i)        = current_pixel + 1;
    }

    return 0;
}
