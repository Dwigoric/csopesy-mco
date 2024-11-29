#ifndef BACKINGSTORE_H
#define BACKINGSTORE_H

#include <string>
#include <vector>

#include "../memory/MemoryManager.h"

class BackingStore {
public:
	static void initialize();
	static BackingStore* getInstance();
	static void destroy();

	void savePage(const std::string& filename, int pid, int instructionLine, int totalInstructionLines, int pageSize);
	std::vector<int> loadPage(const std::string& filename);

	void saveProcess(const std::string& filename, int pid, int instructionLine, int totalInstructionLines);
	std::vector<int> loadProcess(const std::string& filename);

	size_t getNumPagedIn();
	size_t getNumPagedOut();
private:
	static BackingStore* sharedInstance;

	size_t numPagedIn = 0;
	size_t numPagedOut = 0;

	BackingStore();
	~BackingStore() = default;
};

#endif // BACKINGSTORE_H