#ifndef FIRSTFITFLATALLOCATOR_H
#define FIRSTFITFLATALLOCATOR_H


#include <cstdint>
#include <vector>
#include <sstream>
#include <mutex>

#include "IMemoryAllocator.h"
#include "../process/Process.h"

class FirstFitFlatAllocator : public IMemoryAllocator {
public:
	FirstFitFlatAllocator(uint8_t* memory, size_t totalMemory, size_t frameSize);

	void* allocate(std::shared_ptr<Process> process) override;
	void deallocate(std::shared_ptr<Process> process) override;
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

#endif //FIRSTFITFLATALLOCATOR_H

