#include "main.h"

#include "cpu/CPUManager.h"
#include "threading/SchedulerThread.h"

int main() {
	CPUManager::initialize(4);
	SchedulerThread::initialize();

	// UNCOMMENT FOR TESTING
	std::shared_ptr<Process> process = std::make_shared<Process>(1, "test");
	process->addCommand(AInstruction::PRINT);
	process->addCommand(AInstruction::PRINT);
	process->addCommand(AInstruction::PRINT);

	std::shared_ptr<Process> process1 = std::make_shared<Process>(2, "test2");
	process1->addCommand(AInstruction::PRINT);
	process1->addCommand(AInstruction::PRINT);

	CPUManager::getInstance()->startAllCores();
	CPUManager::getInstance()->getCores()[0]->assignProcess(process);
	process->setCore(0);

	CPUManager::getInstance()->getCores()[1]->assignProcess(process1);
	process1->setCore(1);

	SchedulerThread::getInstance()->sleep(100);

	ConsoleManager::initialize();

	// TEMP: should only be called on `initialize` command
	// but called on startup for now
	ConsoleManager::getInstance()->loadConfigs();

	// TEMP: run test case - for Homework 6 Only


	bool terminate = false;

	do {
		ConsoleManager::getInstance()->process();
		ConsoleManager::getInstance()->drawConsole();

		terminate = !ConsoleManager::getInstance()->isRunning();
	} while (!terminate);

	ConsoleManager::destroy();
	CPUManager::destroy();

	return 0;
}
