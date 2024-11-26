#include "BackingStore.h"

#include <fstream>
#include <vector>
#include <stdexcept>

void BackingStore::savePage(int pageSize, const std::vector<size_t>& data, const std::string& filename, size_t page) {
	// Check page size
	if (data.size() != pageSize) {
		throw std::runtime_error("Data size does not match page size");
	}

	std::ofstream outFile(filename, std::ios::out | std::ios::binary);
	if (!outFile.is_open()) {
		throw std::runtime_error("File not found");
	}

	outFile.seekp(page * pageSize);
	outFile.write(reinterpret_cast<const char*>(data.data()), pageSize);
	outFile.close();
}

std::vector<size_t> loadPage(int pageSize, const std::string& filename, size_t page) {
	std::ifstream inFile(filename, std::ios::in | std::ios::binary);
	if (!inFile.is_open()) {
		throw std::runtime_error("File not found");
	}

	std::vector<size_t> data(pageSize);
	inFile.seekg(page * pageSize);
	inFile.read(reinterpret_cast<char*>(data.data()), pageSize);
	inFile.close();

	return data;
}
