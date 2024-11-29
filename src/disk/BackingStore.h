#ifndef BACKINGSTORE_H
#define BACKINGSTORE_H

#include <string>
#include <vector>

class BackingStore {
public:
	static void savePage(int pageSize, const std::vector<size_t>& data, const std::string& filename, size_t page);
	static std::vector<size_t> loadPage(int pageSize, const std::string& filename, size_t page);

	static void saveProcess(int pageSize, const std::vector<size_t>& data, const std::string& filename);
	static std::vector<size_t> loadProcess(int pageSize, const std::string& filename);

private:
	BackingStore() = delete;
	~BackingStore() = delete;

	BackingStore(const BackingStore&) = delete;
	BackingStore& operator=(const BackingStore&) = delete;
};

#endif // BACKINGSTORE_H