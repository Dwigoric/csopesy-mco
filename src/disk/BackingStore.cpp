#include "BackingStore.h"

#include <fstream>

void BackingStore::save(const std::string& data, const std::string& filename) {
	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << data;
		outFile.close();
	}
}

std::string BackingStore::load(const std::string& filename) {
	std::ifstream inFile(filename);
	std::string data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
	return data;
}
