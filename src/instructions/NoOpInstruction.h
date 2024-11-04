#pragma once 

#include "AInstruction.h"

#include <thread>
#include <chrono>

class NoOpInstruction : public AInstruction {
public:
	NoOpInstruction();
	void execute(int core = 0) override;
};