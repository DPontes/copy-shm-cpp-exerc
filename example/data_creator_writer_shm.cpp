#include "memory.h"
#include <cstdio>
#include <iostream>
#include <thread>

using namespace boost::interprocess;

int main()
{
    createdMemory mem;

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
