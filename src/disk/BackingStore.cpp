#include "BackingStore.h"

#include <fstream>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <string>

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
	std::filesystem::create_directories("bkstore/pg");
	const std::string path = "bkstore/pg/" + filename;

	std::string pidString = std::to_string(pid);
	std::string instructionLineString = std::to_string(instructionLine);
	std::string totalInstructionLinesString = std::to_string(totalInstructionLines);
	std::string pageSizeString = std::to_string(pageSize);

	std::ofstream outFile(path, std::ios::out);
	// Store pid, instruction line, total instruction lines, and page size
	outFile.write(reinterpret_cast<const char*>(pidString.c_str()), sizeof(pid));
	outFile.write(reinterpret_cast<const char*>(instructionLineString.c_str()), sizeof(instructionLine));
	outFile.write(reinterpret_cast<const char*>(totalInstructionLinesString.c_str()), sizeof(totalInstructionLines));
	outFile.write(reinterpret_cast<const char*>(pageSizeString.c_str()), sizeof(pageSize));

	numPagedOut++;

	outFile.close();
}

std::vector<int> BackingStore::loadPage(const std::string& filename) {
	std::filesystem::create_directories("bkstore/pg");
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
	std::filesystem::create_directories("bkstore/proc");
	const std::string path = "bkstore/proc/" + filename;

	std::string pidString = std::to_string(pid);
	std::string instructionLineString = std::to_string(instructionLine);
	std::string totalInstructionLinesString = std::to_string(totalInstructionLines);

	std::ofstream outFile(path, std::ios::out | std::ios::binary);
	// Store pid, instruction line, and total instruction lines
	outFile.write(reinterpret_cast<const char*>(pidString.c_str()), sizeof(pid));
	outFile.write(reinterpret_cast<const char*>(instructionLineString.c_str()), sizeof(instructionLine));
	outFile.write(reinterpret_cast<const char*>(totalInstructionLinesString.c_str()), sizeof(totalInstructionLines));

	outFile.close();
}

std::vector<int> BackingStore::loadProcess(const std::string& filename) {
	std::filesystem::create_directories("bkstore/proc");
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
