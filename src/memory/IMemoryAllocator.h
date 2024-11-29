#ifndef IMEMORYALLOCATOR_H
#define IMEMORYALLOCATOR_H

#include <string>
#include <vector>

class IMemoryAllocator {
public:
	virtual void* allocate(const int pid, size_t size) = 0;
	virtual void deallocate(const int pid) = 0;
	virtual std::string visualizeMemory() = 0;

	virtual std::vector<int>& getAllocationMap() = 0;
	virtual size_t getAllocatedSize() = 0;
};

#endif //IMEMORYALLOCATOR_H

