#pragma once

#include <cstdint>
#include <vector>
#include <sstream>

#include "IMemoryAllocator.h"

class FirstFitFlatAllocator : public IMemoryAllocator {
public:
	FirstFitFlatAllocator(uint8_t* memory, size_t totalMemory, size_t frameSize);

	void* allocate(const int pid, size_t size) override;
	void deallocate(const int pid) override;
	std::string visualizeMemory() override;

	std::vector<int>& getAllocationMap() override;
	size_t getAllocatedSize() override;
private:
	uint8_t* memory;
	std::vector<int> allocationMap;

	size_t totalMemory;
	size_t frameSize;
	size_t allocatedSize;

	void allocateAt(const int pid, size_t start, size_t size);
	void deallocateAt(size_t start, size_t size);
};