#ifndef IMEMORYALLOCATOR_H
#define IMEMORYALLOCATOR_H

#include <string>
#include <vector>

#include "../process/Process.h"

class IMemoryAllocator {
public:
	virtual void* allocate(std::shared_ptr<Process> process) = 0;
	virtual void deallocate(std::shared_ptr<Process> process) = 0;
	virtual std::string visualizeMemory() = 0;

	virtual std::vector<int>& getAllocationMap() = 0;
	virtual size_t getAllocatedSize() = 0;
};

#endif //IMEMORYALLOCATOR_H

