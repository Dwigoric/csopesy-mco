#include "PrintInstruction.h"
#include <iostream>

PrintInstruction::PrintInstruction(int pid, std::string& toPrint) : AInstruction(pid, PRINT) {
	this->toPrint = toPrint;
}

void PrintInstruction::execute() {
	std::cout << "PID " << this->pid << ":" << this->toPrint << "\n";
}