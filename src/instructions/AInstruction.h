#ifndef AINSTRUCTION_H
#define AINSTRUCTION_H

class AInstruction {
public:
	enum InstructionType {
		PRINT,
		NOOP
	};

	AInstruction(int pid, InstructionType instructionType);
	InstructionType getInstructionType() const;
	virtual void execute(int core) = 0;

	AInstruction() = default;

protected:
	int pid;
	InstructionType instructionType;
};

inline AInstruction::AInstruction(int pid, InstructionType instructionType) {
	this->pid = pid;
	this->instructionType = instructionType;
}

inline AInstruction::InstructionType AInstruction::getInstructionType() const {
	return this->instructionType;
}

#endif //AINSTRUCTION_H