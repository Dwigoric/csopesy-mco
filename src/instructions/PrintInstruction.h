#ifndef PRINTINSTRUCTION_H
#define PRINTINSTRUCTION_H

#include "AInstruction.h"
#include <string>
#include <fstream>
#include <optional>

class PrintInstruction : public AInstruction {
public:
	PrintInstruction(int pid, std::string& toPrint, const std::string filename="");
	void execute(int core=0) override;

private:
	std::string toPrint;
	std::string filename;
};

#endif //PRINTINSTRUCTION_H