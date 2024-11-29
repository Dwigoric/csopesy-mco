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

	void savePage(int pageSize, const std::vector<size_t>& data, const std::string& filename, size_t page);
	std::vector<size_t> loadPage(int pageSize, const std::string& filename, size_t page);

	void saveProcess(int pageSize, const std::vector<size_t>& data, const std::string& filename);
	std::vector<size_t> loadProcess(int pageSize, const std::string& filename);

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