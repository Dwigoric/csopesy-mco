#ifndef PRINTINSTRUCTION_H
#define PRINTINSTRUCTION_H

#include "AInstruction.h"
#include <string>

class PrintInstruction : public AInstruction {
public:
	PrintInstruction(int pid, std::string& toPrint);
	void execute() override;

private:
	std::string toPrint;
};

#endif //PRINTINSTRUCTION_H