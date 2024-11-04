#include "NoOpInstruction.h"

NoOpInstruction::NoOpInstruction()
{
}

void NoOpInstruction::execute(int core)
{
	std::this_thread::sleep_for(std::chrono::microseconds(1));
}
