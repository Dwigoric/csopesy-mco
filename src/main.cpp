#include "main.h"

#include "cpu/CPUManager.h"
#include "threading/SchedulerThread.h"

int main() {
	ConsoleManager::initialize();

	bool terminate = false;

	do {
		ConsoleManager::getInstance()->process();
		ConsoleManager::getInstance()->drawConsole();

		terminate = !ConsoleManager::getInstance()->isRunning();
	} while (!terminate);

	ConsoleManager::destroy();

	return 0;
}
