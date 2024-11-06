#pragma once

#include <string>

class IMemoryAllocator {
public:
	virtual void* allocate(const int pid, size_t size) = 0;
	virtual void deallocate(const int pid) = 0;
	virtual std::string visualizeMemory() = 0;

	virtual size_t getAllocatedSize() = 0;
};