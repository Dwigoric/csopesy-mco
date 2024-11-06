#pragma once

#include <cstdint>
#include <iostream>

#include "../console/ConsoleManager.h"

class MemoryManager {
public:
	static MemoryManager* getInstance();
	static void initialize();
	static void destroy();

private:
	static MemoryManager* sharedInstance;
	static int x;

	uint8_t* memory;

	MemoryManager();
	~MemoryManager() = default;
	MemoryManager(MemoryManager const&) {};

	size_t totalMemory;
	size_t frameSize;
};