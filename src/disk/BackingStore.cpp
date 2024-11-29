#include "BackingStore.h"

#include <fstream>
#include <vector>
#include <stdexcept>

BackingStore* BackingStore::sharedInstance = nullptr;

void BackingStore::initialize()
{
	sharedInstance = new BackingStore();
}

BackingStore* BackingStore::getInstance()
{
	return sharedInstance;
}

void BackingStore::destroy()
{
	delete sharedInstance;
}

void BackingStore::savePage(const std::string& filename, int pid, int instructionLine, int totalInstructionLines, int pageSize) {
	const std::string path = "bkstore/pg/" + filename;

	std::ofstream outFile(path, std::ios::out | std::ios::binary);
	// Store pid, instruction line, total instruction lines, and page size
	outFile.write(reinterpret_cast<const char*>(&pid), sizeof(pid));
	outFile.write(reinterpret_cast<const char*>(&instructionLine), sizeof(instructionLine));
	outFile.write(reinterpret_cast<const char*>(&totalInstructionLines), sizeof(totalInstructionLines));
	outFile.write(reinterpret_cast<const char*>(&pageSize), sizeof(pageSize));

	numPagedOut++;

	outFile.close();
}

std::vector<int> BackingStore::loadPage(const std::string& filename) {
	const std::string path = "bkstore/pg/" + filename;

	std::ifstream inFile(path, std::ios::in | std::ios::binary);
	if (!inFile.is_open()) {
		throw std::runtime_error("File not found");
	}

	// Read pid, instruction line, total instruction lines, and page size
	int pid;
	int instructionLine;
	int totalInstructionLines;
	int pageSize;
	inFile.read(reinterpret_cast<char*>(&pid), sizeof(pid));
	inFile.read(reinterpret_cast<char*>(&instructionLine), sizeof(instructionLine));
	inFile.read(reinterpret_cast<char*>(&totalInstructionLines), sizeof(totalInstructionLines));
	inFile.read(reinterpret_cast<char*>(&pageSize), sizeof(pageSize));

	inFile.close();

	numPagedIn++;

	return { pid, instructionLine, totalInstructionLines, pageSize };
}

void BackingStore::saveProcess(const std::string& filename, int pid, int instructionLine, int totalInstructionLines) {
	const std::string path = "bkstore/proc/" + filename;

	std::ofstream outFile(path, std::ios::out | std::ios::binary);
	// Store pid, instruction line, and total instruction lines
	outFile.write(reinterpret_cast<const char*>(&pid), sizeof(pid));
	outFile.write(reinterpret_cast<const char*>(&instructionLine), sizeof(instructionLine));
	outFile.write(reinterpret_cast<const char*>(&totalInstructionLines), sizeof(totalInstructionLines));

	outFile.close();
}

std::vector<int> BackingStore::loadProcess(const std::string& filename) {
	const std::string path = "bkstore/proc/" + filename;

	std::ifstream inFile(path, std::ios::in | std::ios::binary);
	if (!inFile.is_open()) {
		throw std::runtime_error("File not found");
	}

	// Read pid, instruction line, and total instruction lines
	int pid;
	int instructionLine;
	int totalInstructionLines;
	inFile.read(reinterpret_cast<char*>(&pid), sizeof(pid));
	inFile.read(reinterpret_cast<char*>(&instructionLine), sizeof(instructionLine));
	inFile.read(reinterpret_cast<char*>(&totalInstructionLines), sizeof(totalInstructionLines));

	inFile.close();

	return { pid, instructionLine, totalInstructionLines };
}

size_t BackingStore::getNumPagedIn()
{
	return this->numPagedIn;
}

size_t BackingStore::getNumPagedOut()
{
	return this->numPagedOut;
}

BackingStore::BackingStore()
{
}
