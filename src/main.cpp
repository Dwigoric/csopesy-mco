#include "main.h"

#include "cpu/CPUManager.h"
#include "threading/SchedulerThread.h"

int main() {
	CPUManager::initialize(4);
	SchedulerThread::initialize();

	CPUManager::getInstance()->startAllCores();	
	SchedulerThread::getInstance()->start();

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
	SchedulerThread::getInstance()->stopScheduler();
	
	SchedulerThread::getInstance()->sleep(100);

	SchedulerThread::destroy();
	CPUManager::destroy();

	return 0;
}
