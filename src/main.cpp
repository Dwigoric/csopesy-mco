#include "main.h"

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
