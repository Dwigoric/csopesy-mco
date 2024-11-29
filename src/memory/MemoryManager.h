#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <cstdint>
#include <iostream>
#include <memory>

#include "IMemoryAllocator.h"

#include "../console/ConsoleManager.h"

class MemoryManager {
public:
	enum AllocatorType {
		FIRST_FIT_FLAT_ALLOCATOR,
		PAGING_ALLOCATOR
	};

	static MemoryManager* getInstance();

	static void initialize();

	static void destroy();

	void printDetails(std::ostream& os) const;
	size_t getTotalMemory() const;
	std::unordered_map<int, int> getProcessMemoryUsage() const;

	std::shared_ptr<IMemoryAllocator> getAllocator() const;


private:
	static MemoryManager *sharedInstance;

	uint8_t *memory{};
	std::shared_ptr<IMemoryAllocator> allocator;

	MemoryManager();

	~MemoryManager() = default;

	MemoryManager(MemoryManager const &) {
	};

	size_t totalMemory{};
	size_t frameSize{};

	size_t numPagedIn = 0;
	size_t numPagedOut = 0;

	AllocatorType allocatorType;

	[[nodiscard]] int computeExternalFragmentation() const;
};
#endif //MEMORYMANAGER_H
