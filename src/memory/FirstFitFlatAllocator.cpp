#include "FirstFitFlatAllocator.h"

#include <iostream>

FirstFitFlatAllocator::FirstFitFlatAllocator(uint8_t* memory, size_t totalMemory, size_t frameSize)
	: memory(memory), totalMemory(totalMemory), frameSize(frameSize), allocatedSize(0)
{
	this->allocationMap = std::vector<int>(totalMemory, -1);
}

void* FirstFitFlatAllocator::allocate(const std::shared_ptr<Process> process)
{
	const int pid = process->getId();
	const size_t size = process->getMemoryRequired();

	size_t startIndex = 0;
	size_t blockLength = 0;

	auto it = std::find(allocationMap.begin(), allocationMap.end(), pid);
	if (it != allocationMap.end()) {
		return &(*it);
	}

	// loop until a block of memory with sufficient length is found
	for (size_t i = 0; i < allocationMap.size(); i++) {
		if (allocationMap[i] == -1) {
			blockLength++;
		}
		else {
			startIndex = i + 1;
			blockLength = 0;
		}

		if (blockLength >= size) {
			allocateAt(pid, startIndex, blockLength);
			return memory + startIndex;
		}
	}

	// no block with sufficient length was found
	return nullptr;
}

void FirstFitFlatAllocator::deallocate(const std::shared_ptr<Process> process)
{
	const int pid = process->getId();

	size_t startIndex = -1;

	// assumes that memory of each process is a contiguous block
	// get start and end of process block
	for (size_t i = 0; i < allocationMap.size(); i++) {
		// found start of block
		if (allocationMap[i] == pid && startIndex == -1) {
			startIndex = i;
		}

		// found end of block
		else if (allocationMap[i] != pid && startIndex != -1) {
			deallocateAt(startIndex, i - startIndex);
			return;
		}
	}

	// if the block extends to the end of the allocation map, dealloc
	if (startIndex != -1) {
		deallocateAt(startIndex, this->totalMemory - startIndex);
	}
}

std::string FirstFitFlatAllocator::visualizeMemory()
{
	std::stringstream ss("");

	ss << "Memory: \n"
		<< std::string(memory, memory + totalMemory)
		<< "\nAllocationMap: \n";

	for (int b : allocationMap) {
		ss << (b != -1 ? std::to_string(b) : ".");
	}

	ss << "\n";

	return ss.str();
}

void FirstFitFlatAllocator::allocateAt(const int pid, size_t start, size_t size)
{
	std::fill(allocationMap.begin() + start, allocationMap.begin() + start + size, pid);
	this->allocatedSize += size;
}

void FirstFitFlatAllocator::deallocateAt(size_t start, size_t size)
{
	std::fill(allocationMap.begin() + start, allocationMap.begin() + start + size, -1);
	this->allocatedSize -= size;
}

std::vector<int>& FirstFitFlatAllocator::getAllocationMap()
{
	return this->allocationMap;
}

size_t FirstFitFlatAllocator::getAllocatedSize()
{
	return this->allocatedSize;
}
