#pragma once

#include <cstdint>
#include <iostream>
#include <memory>

#include "IMemoryAllocator.h"
#include "FirstFitFlatAllocator.h"

#include "../console/ConsoleManager.h"

class MemoryManager {
public:
	static MemoryManager* getInstance();
	static void initialize();
	static void destroy();

private:
	static MemoryManager* sharedInstance;

	uint8_t* memory;
	std::shared_ptr<IMemoryAllocator> allocator;

	MemoryManager();
	~MemoryManager() = default;
	MemoryManager(MemoryManager const&) {};

	size_t totalMemory;
	size_t frameSize;
};