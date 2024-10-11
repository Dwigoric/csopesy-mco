#include "MainConsole.h"
#include "ConsoleManager.h"
#include "../commands/SchedulerStopCommand.h"
#include "../commands/SchedulerTestCommand.h"
#include "../util/string-tokenizer.h"

#include "../commands/ScreenCommand.h"

void MainConsole::onEnabled() {
	// Practice: Set 50 dummy processes
	for (int i = 0; i < DUMMY_PROCESS_COUNT; i++) {
		processes.emplace_back(i, "process_" + std::to_string(i));
	}

	printHeader();
}

void MainConsole::display() {
}

void MainConsole::process() {
	std::string fullCommand;

	printCommandPrefix();

	std::getline(std::cin, fullCommand);

	const std::vector<std::string> commandTokens = tokenize(fullCommand, "[ ]+");
	const std::string &command = commandTokens[0];
	const auto commandParameters = std::vector(commandTokens.begin() + 1, commandTokens.end());

	if (command == "exit") ConsoleManager::getInstance()->exitApplication();
	else if (command == "clear") clear();
	else if (command == "initialize") initialize();
	else if (command == "scheduler-test") SchedulerTestCommand::execute();
	else if (command == "scheduler-stop") SchedulerStopCommand::execute();
	else if (command == "report-util") report_util();
	else if (command == "screen") {
		ScreenCommand::execute(commandParameters, processes);
	} else {
		std::cout << "Commands list:\n";
		std::cout << "exit - exit the program\n";
		std::cout << "clear - clear the screen\n";
		std::cout << "initialize - initialize the program\n";
		std::cout << "scheduler-test - test the scheduler\n";
		std::cout << "scheduler-stop - stop the scheduler\n";
		std::cout << "report-util - display the report utility\n";
		std::cout << "screen - manage screens\n";
	}
}

// Command functions
void MainConsole::initialize() {
	std::cout << "`initialize` command recognized. Doing something.\n";
}

void MainConsole::report_util() {
	std::cout << "`report-util` command recognized. Doing something.\n";
}

// Basic display functions
void MainConsole::printHeader() {
	std::cout << "a88888b. .d88888b   .88888.   888888ba   88888888b .d88888b  dP    dP\n";
	std::cout << "d8'   `88 88.    \"' d8'   `8b  88    `8b  88        88.    \"' Y8.  .8P\n";
	std::cout << "88        `Y88888b. 88     88 a88aaaa8P' a88aaaa    `Y88888b.  Y8aa8P\n";
	std::cout << "88              `8b 88     88  88         88              `8b    88\n";
	std::cout << "Y8.   .88 d8'   .8P Y8.   .8P  88         88        d8'   .8P    88\n";
	std::cout << "Y88888P'  Y88888P   `8888P'   dP         88888888P  Y88888P     dP\n";
	std::cout << "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\n";
	std::cout << "Hello! Welcome to the CSOPESY command line.\n";
	std::cout << "Type 'exit' to exit, 'clear' to clear the screen\n";
}

void MainConsole::printCommandPrefix() {
	std::cout << "user@CSOPESY:~$ ";
}

void MainConsole::clear() {
	ConsoleManager::getInstance()->clearScreen();
	printHeader();
}
