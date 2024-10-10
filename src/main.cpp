#include "main.h"

int main() {
	ConsoleManager::initialize();

	// TEMP: should only be called on `initialize` command
	// but called on startup for now
	ConsoleManager::getInstance()->loadConfigs();

	bool terminate = false;

	do {
		ConsoleManager::getInstance()->process();
		ConsoleManager::getInstance()->drawConsole();

		terminate = !ConsoleManager::getInstance()->isRunning();
	} while (!terminate);

	ConsoleManager::destroy();

	return 0;
}
