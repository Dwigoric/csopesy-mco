#ifndef BACKINGSTORE_H
#define BACKINGSTORE_H

#include <string>

class BackingStore {
public:
	static void save(const std::string& data, const std::string& filename);
	static std::string load(const std::string& filename);

private:
	BackingStore() = delete;
	~BackingStore() = delete;

	BackingStore(const BackingStore&) = delete;
	BackingStore& operator=(const BackingStore&) = delete;
};

#endif // BACKINGSTORE_H