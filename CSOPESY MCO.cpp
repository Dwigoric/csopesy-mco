// CSOPESY MCO.cpp : Defines the entry point for the application.
//

#include "CSOPESY MCO.h"

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