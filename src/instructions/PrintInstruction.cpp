#include "PrintInstruction.h"
#include <iostream>
#include <ctime>
#include <chrono>

PrintInstruction::PrintInstruction(int pid, std::string& toPrint, const std::string filename) : AInstruction(pid, PRINT) {
	this->toPrint = toPrint;
	this->filename = filename;
}

void PrintInstruction::execute(int core) {
	if (this->filename == "") {
		time_t now = time(0);
		std::tm* localTime = std::localtime(&now);
		std::stringstream ss;
		ss << std::put_time(localTime, "%m/%d/%Y %I:%M:%S%p");

		std::cout << "(" << ss.str() << ") Core:" << core << " \"" << this->toPrint << "\"\n";
	}
	else {
		std::ofstream fs;
		fs.open(this->filename, std::ios_base::app);

		time_t now = time(0);
		std::tm* localTime = std::localtime(&now);
		std::stringstream ss;
		ss << std::put_time(localTime, "%m/%d/%Y %I:%M:%S%p");

		fs << "(" << ss.str() << ") Core:" << core << " \"" << this->toPrint << "\"\n";
		fs.close();
	}
}