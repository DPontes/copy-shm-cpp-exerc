#include "memory.h"

// Memory Contructor
Memory::Memory() {}

// Memory Destructor
Memory::~Memory() {}

// maps the memory region to be used
void Memory::mapRegion()
{
  region = mapped_region(shm, read_write);
}

void* Memory::getRegionAddress()
{
  return region.get_address();
}


Memory::createdMemory()
{
  shared_memory_object::remove("MySharedMemory");
}

Memory::~createdMemory()
{
  shared_memory_object::remove("MySharedMemory");
}

void createdMemory::createMemObj()
{
  shm = shared_memory_object(create_only, "MySharedMemory", read_write);
}

void createdMemory::setSize()
{
  shm.truncate(sizeof(Image));
}


Memory::openedMemory() {}

Memory::~openedMemory()
{
  shared_memory_object::remove("MySharedMemory");
}

void openedMemory::openMemObj()
{
  shm = shared_memory_object(open_only, "MySharedMemory", read_write);
}

