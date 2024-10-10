#include "PrintInstruction.h"
#include <iostream>

PrintInstruction::PrintInstruction(int pid, std::string& toPrint, const std::string filename) : AInstruction(pid, PRINT) {
	this->toPrint = toPrint;
	this->filename = filename;
}

void PrintInstruction::execute() {
	if (this->filename == "") {
		std::cout << "PID " << this->pid << ":" << this->toPrint << "\n";
	}
	else {
		std::fstream fs(this->filename);
		fs << "PID " << this->pid << ":" << this->toPrint << "\n";
		fs.close();
	}
}