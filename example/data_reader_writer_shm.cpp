#include "memory.h"
#include <cstdio>
#include <iostream>

using namespace boost::interprocess;

int main()
{
    openedMemory mem;

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
